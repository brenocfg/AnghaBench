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
typedef  enum dc_link_rate { ____Placeholder_dc_link_rate } dc_link_rate ;

/* Variables and functions */
 int LINK_RATE_LOW ; 

__attribute__((used)) static inline bool reached_minimum_link_rate(enum dc_link_rate link_rate)
{
	return link_rate <= LINK_RATE_LOW;
}