#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct st_proto_s {size_t chnl_id; void* write; int /*<<< orphan*/ * reg_complete_cb; int /*<<< orphan*/ * recv; } ;
struct st_data_s {int* is_registered; scalar_t__ protos_registered; int /*<<< orphan*/  lock; int /*<<< orphan*/  st_state; int /*<<< orphan*/  kim_data; } ;

/* Variables and functions */
 long EALREADY ; 
 long EINPROGRESS ; 
 long EINVAL ; 
 long EPROTONOSUPPORT ; 
 scalar_t__ ST_EMPTY ; 
 size_t ST_MAX_CHANNELS ; 
 int /*<<< orphan*/  ST_REG_IN_PROGRESS ; 
 int /*<<< orphan*/  ST_REG_PENDING ; 
 int /*<<< orphan*/  add_channel_to_table (struct st_data_s*,struct st_proto_s*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,size_t) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  st_int_recv ; 
 int /*<<< orphan*/  st_kim_recv ; 
 int /*<<< orphan*/  st_kim_ref (struct st_data_s**,int /*<<< orphan*/ ) ; 
 long st_kim_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_ll_enable (struct st_data_s*) ; 
 int /*<<< orphan*/  st_recv ; 
 int /*<<< orphan*/  st_reg_complete (struct st_data_s*,long) ; 
 void* st_write ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

long st_register(struct st_proto_s *new_proto)
{
	struct st_data_s	*st_gdata;
	long err = 0;
	unsigned long flags = 0;

	st_kim_ref(&st_gdata, 0);
	if (st_gdata == NULL || new_proto == NULL || new_proto->recv == NULL
	    || new_proto->reg_complete_cb == NULL) {
		pr_err("gdata/new_proto/recv or reg_complete_cb not ready");
		return -EINVAL;
	}

	if (new_proto->chnl_id >= ST_MAX_CHANNELS) {
		pr_err("chnl_id %d not supported", new_proto->chnl_id);
		return -EPROTONOSUPPORT;
	}

	if (st_gdata->is_registered[new_proto->chnl_id] == true) {
		pr_err("chnl_id %d already registered", new_proto->chnl_id);
		return -EALREADY;
	}

	/* can be from process context only */
	spin_lock_irqsave(&st_gdata->lock, flags);

	if (test_bit(ST_REG_IN_PROGRESS, &st_gdata->st_state)) {
		pr_info(" ST_REG_IN_PROGRESS:%d ", new_proto->chnl_id);
		/* fw download in progress */

		add_channel_to_table(st_gdata, new_proto);
		st_gdata->protos_registered++;
		new_proto->write = st_write;

		set_bit(ST_REG_PENDING, &st_gdata->st_state);
		spin_unlock_irqrestore(&st_gdata->lock, flags);
		return -EINPROGRESS;
	} else if (st_gdata->protos_registered == ST_EMPTY) {
		pr_info(" chnl_id list empty :%d ", new_proto->chnl_id);
		set_bit(ST_REG_IN_PROGRESS, &st_gdata->st_state);
		st_recv = st_kim_recv;

		/* enable the ST LL - to set default chip state */
		st_ll_enable(st_gdata);

		/* release lock previously held - re-locked below */
		spin_unlock_irqrestore(&st_gdata->lock, flags);

		/* this may take a while to complete
		 * since it involves BT fw download
		 */
		err = st_kim_start(st_gdata->kim_data);
		if (err != 0) {
			clear_bit(ST_REG_IN_PROGRESS, &st_gdata->st_state);
			if ((st_gdata->protos_registered != ST_EMPTY) &&
			    (test_bit(ST_REG_PENDING, &st_gdata->st_state))) {
				pr_err(" KIM failure complete callback ");
				spin_lock_irqsave(&st_gdata->lock, flags);
				st_reg_complete(st_gdata, err);
				spin_unlock_irqrestore(&st_gdata->lock, flags);
				clear_bit(ST_REG_PENDING, &st_gdata->st_state);
			}
			return -EINVAL;
		}

		spin_lock_irqsave(&st_gdata->lock, flags);

		clear_bit(ST_REG_IN_PROGRESS, &st_gdata->st_state);
		st_recv = st_int_recv;

		/* this is where all pending registration
		 * are signalled to be complete by calling callback functions
		 */
		if ((st_gdata->protos_registered != ST_EMPTY) &&
		    (test_bit(ST_REG_PENDING, &st_gdata->st_state))) {
			pr_debug(" call reg complete callback ");
			st_reg_complete(st_gdata, 0);
		}
		clear_bit(ST_REG_PENDING, &st_gdata->st_state);

		/* check for already registered once more,
		 * since the above check is old
		 */
		if (st_gdata->is_registered[new_proto->chnl_id] == true) {
			pr_err(" proto %d already registered ",
				   new_proto->chnl_id);
			spin_unlock_irqrestore(&st_gdata->lock, flags);
			return -EALREADY;
		}

		add_channel_to_table(st_gdata, new_proto);
		st_gdata->protos_registered++;
		new_proto->write = st_write;
		spin_unlock_irqrestore(&st_gdata->lock, flags);
		return err;
	}
	/* if fw is already downloaded & new stack registers protocol */
	else {
		add_channel_to_table(st_gdata, new_proto);
		st_gdata->protos_registered++;
		new_proto->write = st_write;

		/* lock already held before entering else */
		spin_unlock_irqrestore(&st_gdata->lock, flags);
		return err;
	}
}