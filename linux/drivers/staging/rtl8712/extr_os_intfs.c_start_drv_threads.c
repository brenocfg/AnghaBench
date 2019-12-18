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
typedef  int /*<<< orphan*/  u32 ;
struct _adapter {int /*<<< orphan*/  cmd_thread; TYPE_1__* pnetdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct _adapter*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_cmd_thread ; 

__attribute__((used)) static u32 start_drv_threads(struct _adapter *padapter)
{
	padapter->cmd_thread = kthread_run(r8712_cmd_thread, padapter, "%s",
					  padapter->pnetdev->name);
	if (IS_ERR(padapter->cmd_thread))
		return _FAIL;
	return _SUCCESS;
}