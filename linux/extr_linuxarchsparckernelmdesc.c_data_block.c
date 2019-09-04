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
struct mdesc_hdr {int name_sz; } ;

/* Variables and functions */
 scalar_t__ name_block (struct mdesc_hdr*) ; 

__attribute__((used)) static void *data_block(struct mdesc_hdr *mdesc)
{
	return ((void *) name_block(mdesc)) + mdesc->name_sz;
}