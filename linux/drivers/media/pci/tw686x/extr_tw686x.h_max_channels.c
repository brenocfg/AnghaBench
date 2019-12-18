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
struct tw686x_dev {unsigned int type; } ;

/* Variables and functions */
 unsigned int TYPE_MAX_CHANNELS ; 

__attribute__((used)) static inline unsigned int max_channels(struct tw686x_dev *dev)
{
	return dev->type & TYPE_MAX_CHANNELS; /* 4 or 8 channels */
}