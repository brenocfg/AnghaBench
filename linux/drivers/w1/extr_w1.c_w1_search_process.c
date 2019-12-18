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
typedef  int /*<<< orphan*/  u8 ;
struct w1_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  w1_search_process_cb (struct w1_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_slave_found ; 

__attribute__((used)) static void w1_search_process(struct w1_master *dev, u8 search_type)
{
	w1_search_process_cb(dev, search_type, w1_slave_found);
}