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
struct timer_list {int dummy; } ;
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 struct mwifiex_adapter* adapter ; 
 int /*<<< orphan*/  devdump_timer ; 
 struct mwifiex_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_upload_device_dump (struct mwifiex_adapter*) ; 

__attribute__((used)) static void fw_dump_timer_fn(struct timer_list *t)
{
	struct mwifiex_adapter *adapter = from_timer(adapter, t, devdump_timer);

	mwifiex_upload_device_dump(adapter);
}