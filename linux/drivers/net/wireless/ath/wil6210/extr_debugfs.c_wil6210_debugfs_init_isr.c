#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wil6210_priv {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  icr_off; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* dbg_icr ; 
 int /*<<< orphan*/  wil6210_debugfs_create_ISR (struct wil6210_priv*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wil6210_debugfs_init_isr(struct wil6210_priv *wil,
				     struct dentry *dbg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dbg_icr); i++)
		wil6210_debugfs_create_ISR(wil, dbg_icr[i].name, dbg,
					   dbg_icr[i].icr_off);
}