#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mwifiex_private {int dummy; } ;
struct mwifiex_if_ops {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* init_if ) (struct mwifiex_adapter*) ;} ;
struct mwifiex_adapter {int priv_num; struct mwifiex_adapter** priv; int /*<<< orphan*/  cmd_timer; struct mwifiex_adapter* adapter; TYPE_1__ if_ops; int /*<<< orphan*/  debug_mask; void* card; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWIFIEX_MAX_BSS_NUM ; 
 int /*<<< orphan*/  debug_mask ; 
 int /*<<< orphan*/  kfree (struct mwifiex_adapter*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,struct mwifiex_if_ops*,int) ; 
 int /*<<< orphan*/  mwifiex_cmd_timeout_func ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_init_lock_list (struct mwifiex_adapter*) ; 
 scalar_t__ stub1 (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_register(void *card, struct device *dev,
			    struct mwifiex_if_ops *if_ops, void **padapter)
{
	struct mwifiex_adapter *adapter;
	int i;

	adapter = kzalloc(sizeof(struct mwifiex_adapter), GFP_KERNEL);
	if (!adapter)
		return -ENOMEM;

	*padapter = adapter;
	adapter->dev = dev;
	adapter->card = card;

	/* Save interface specific operations in adapter */
	memmove(&adapter->if_ops, if_ops, sizeof(struct mwifiex_if_ops));
	adapter->debug_mask = debug_mask;

	/* card specific initialization has been deferred until now .. */
	if (adapter->if_ops.init_if)
		if (adapter->if_ops.init_if(adapter))
			goto error;

	adapter->priv_num = 0;

	for (i = 0; i < MWIFIEX_MAX_BSS_NUM; i++) {
		/* Allocate memory for private structure */
		adapter->priv[i] =
			kzalloc(sizeof(struct mwifiex_private), GFP_KERNEL);
		if (!adapter->priv[i])
			goto error;

		adapter->priv[i]->adapter = adapter;
		adapter->priv_num++;
	}
	mwifiex_init_lock_list(adapter);

	timer_setup(&adapter->cmd_timer, mwifiex_cmd_timeout_func, 0);

	return 0;

error:
	mwifiex_dbg(adapter, ERROR,
		    "info: leave mwifiex_register with error\n");

	for (i = 0; i < adapter->priv_num; i++)
		kfree(adapter->priv[i]);

	kfree(adapter);

	return -1;
}