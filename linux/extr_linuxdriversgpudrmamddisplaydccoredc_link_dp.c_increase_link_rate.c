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
#define  LINK_RATE_HIGH 130 
#define  LINK_RATE_HIGH2 129 
 int LINK_RATE_HIGH3 ; 
#define  LINK_RATE_LOW 128 
 int LINK_RATE_UNKNOWN ; 

__attribute__((used)) static enum dc_link_rate increase_link_rate(enum dc_link_rate link_rate)
{
	switch (link_rate) {
	case LINK_RATE_LOW:
		return LINK_RATE_HIGH;
	case LINK_RATE_HIGH:
		return LINK_RATE_HIGH2;
	case LINK_RATE_HIGH2:
		return LINK_RATE_HIGH3;
	default:
		return LINK_RATE_UNKNOWN;
	}
}