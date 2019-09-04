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
struct go7007 {int dummy; } ;

/* Variables and functions */
 int go7007_init_encoder (struct go7007*) ; 
 scalar_t__ go7007_load_encoder (struct go7007*) ; 

int go7007_reset_encoder(struct go7007 *go)
{
	if (go7007_load_encoder(go) < 0)
		return -1;
	return go7007_init_encoder(go);
}