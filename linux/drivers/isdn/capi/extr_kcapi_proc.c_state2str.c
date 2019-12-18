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

/* Variables and functions */
#define  CAPI_CTR_DETECTED 130 
#define  CAPI_CTR_LOADING 129 
#define  CAPI_CTR_RUNNING 128 

__attribute__((used)) static char *state2str(unsigned short state)
{
	switch (state) {
	case CAPI_CTR_DETECTED:	return "detected";
	case CAPI_CTR_LOADING:	return "loading";
	case CAPI_CTR_RUNNING:	return "running";
	default:	        return "???";
	}
}