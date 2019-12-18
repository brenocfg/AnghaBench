#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pca963x_led {TYPE_2__* chip; } ;
struct TYPE_4__ {TYPE_1__* chipdef; } ;
struct TYPE_3__ {unsigned int scaling; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 

__attribute__((used)) static unsigned int pca963x_period_scale(struct pca963x_led *pca963x,
	unsigned int val)
{
	unsigned int scaling = pca963x->chip->chipdef->scaling;

	return scaling ? DIV_ROUND_CLOSEST(val * scaling, 1000) : val;
}