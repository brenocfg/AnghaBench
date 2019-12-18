#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct c8sectpfei {int tsin_count; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {struct c8sectpfei* priv; } ;
struct c8sectpfe {int num_feeds; TYPE_3__ adapter; TYPE_1__* demux; int /*<<< orphan*/  device; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int tsin_index; struct c8sectpfei* c8sectpfei; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int dvb_register_adapter (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short*) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct c8sectpfe*) ; 
 struct c8sectpfe* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int register_dvb (TYPE_1__*,TYPE_3__*,void*,void*,struct c8sectpfei*) ; 
 int /*<<< orphan*/  unregister_dvb (TYPE_1__*) ; 

__attribute__((used)) static struct c8sectpfe *c8sectpfe_create(struct c8sectpfei *fei,
				void *start_feed,
				void *stop_feed)
{
	struct c8sectpfe *c8sectpfe;
	int result;
	int i, j;

	short int ids[] = { -1 };

	c8sectpfe = kzalloc(sizeof(struct c8sectpfe), GFP_KERNEL);
	if (!c8sectpfe)
		goto err1;

	mutex_init(&c8sectpfe->lock);

	c8sectpfe->device = fei->dev;

	result = dvb_register_adapter(&c8sectpfe->adapter, "STi c8sectpfe",
					THIS_MODULE, fei->dev, ids);
	if (result < 0) {
		dev_err(fei->dev, "dvb_register_adapter failed (errno = %d)\n",
			result);
		goto err2;
	}

	c8sectpfe->adapter.priv = fei;

	for (i = 0; i < fei->tsin_count; i++) {

		c8sectpfe->demux[i].tsin_index = i;
		c8sectpfe->demux[i].c8sectpfei = fei;

		result = register_dvb(&c8sectpfe->demux[i], &c8sectpfe->adapter,
				start_feed, stop_feed, fei);
		if (result < 0) {
			dev_err(fei->dev,
				"register_dvb feed=%d failed (errno = %d)\n",
				result, i);

			/* we take a all or nothing approach */
			for (j = 0; j < i; j++)
				unregister_dvb(&c8sectpfe->demux[j]);
			goto err3;
		}
	}

	c8sectpfe->num_feeds = fei->tsin_count;

	return c8sectpfe;
err3:
	dvb_unregister_adapter(&c8sectpfe->adapter);
err2:
	kfree(c8sectpfe);
err1:
	return NULL;
}