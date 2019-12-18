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
struct host1x {TYPE_1__* debug_op; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* debug_init ) (struct dentry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dentry*) ; 

__attribute__((used)) static inline void host1x_hw_debug_init(struct host1x *host, struct dentry *de)
{
	if (host->debug_op && host->debug_op->debug_init)
		host->debug_op->debug_init(de);
}