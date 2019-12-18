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
struct vc_data {int vc_size_row; } ;

/* Variables and functions */
 int fbcon_softback_size ; 
 scalar_t__ softback_buf ; 
 scalar_t__ softback_end ; 
 scalar_t__ softback_top ; 

__attribute__((used)) static void fbcon_update_softback(struct vc_data *vc)
{
	int l = fbcon_softback_size / vc->vc_size_row;

	if (l > 5)
		softback_end = softback_buf + l * vc->vc_size_row;
	else
		/* Smaller scrollback makes no sense, and 0 would screw
		   the operation totally */
		softback_top = 0;
}