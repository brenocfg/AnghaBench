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
struct device_link {int /*<<< orphan*/  supplier; int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct device_link*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_link_free(struct device_link *link)
{
	put_device(link->consumer);
	put_device(link->supplier);
	kfree(link);
}