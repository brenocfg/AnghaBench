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
typedef  int /*<<< orphan*/  u32 ;
struct vas_window {int /*<<< orphan*/  num_txwins; } ;
struct vas_instance {int /*<<< orphan*/  mutex; scalar_t__* rxwin; } ;
typedef  enum vas_cop_type { ____Placeholder_vas_cop_type } vas_cop_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct vas_window* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct vas_window*) ; 
 int VAS_COP_TYPE_FTW ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct vas_window* get_user_rxwin (struct vas_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vas_window *get_vinst_rxwin(struct vas_instance *vinst,
			enum vas_cop_type cop, u32 pswid)
{
	struct vas_window *rxwin;

	mutex_lock(&vinst->mutex);

	if (cop == VAS_COP_TYPE_FTW)
		rxwin = get_user_rxwin(vinst, pswid);
	else
		rxwin = vinst->rxwin[cop] ?: ERR_PTR(-EINVAL);

	if (!IS_ERR(rxwin))
		atomic_inc(&rxwin->num_txwins);

	mutex_unlock(&vinst->mutex);

	return rxwin;
}