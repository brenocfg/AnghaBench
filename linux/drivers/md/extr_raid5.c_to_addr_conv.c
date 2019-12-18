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
struct stripe_head {scalar_t__ disks; } ;
struct raid5_percpu {int dummy; } ;
typedef  void addr_conv_t ;

/* Variables and functions */
 scalar_t__ to_addr_page (struct raid5_percpu*,int) ; 

__attribute__((used)) static addr_conv_t *to_addr_conv(struct stripe_head *sh,
				 struct raid5_percpu *percpu, int i)
{
	return (void *) (to_addr_page(percpu, i) + sh->disks + 2);
}