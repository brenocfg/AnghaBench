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
struct scsi_device {struct alua_dh_data* handler_data; } ;
struct alua_port_group {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct alua_dh_data {int /*<<< orphan*/  pg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_OPTIMIZE_STPG ; 
 int EINVAL ; 
 int ENXIO ; 
 int SCSI_DH_OK ; 
 struct alua_port_group* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static int alua_set_params(struct scsi_device *sdev, const char *params)
{
	struct alua_dh_data *h = sdev->handler_data;
	struct alua_port_group *pg = NULL;
	unsigned int optimize = 0, argc;
	const char *p = params;
	int result = SCSI_DH_OK;
	unsigned long flags;

	if ((sscanf(params, "%u", &argc) != 1) || (argc != 1))
		return -EINVAL;

	while (*p++)
		;
	if ((sscanf(p, "%u", &optimize) != 1) || (optimize > 1))
		return -EINVAL;

	rcu_read_lock();
	pg = rcu_dereference(h->pg);
	if (!pg) {
		rcu_read_unlock();
		return -ENXIO;
	}
	spin_lock_irqsave(&pg->lock, flags);
	if (optimize)
		pg->flags |= ALUA_OPTIMIZE_STPG;
	else
		pg->flags &= ~ALUA_OPTIMIZE_STPG;
	spin_unlock_irqrestore(&pg->lock, flags);
	rcu_read_unlock();

	return result;
}