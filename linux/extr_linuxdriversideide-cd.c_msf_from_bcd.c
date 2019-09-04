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
struct atapi_msf {void* frame; void* second; void* minute; } ;

/* Variables and functions */
 void* bcd2bin (void*) ; 

__attribute__((used)) static void msf_from_bcd(struct atapi_msf *msf)
{
	msf->minute = bcd2bin(msf->minute);
	msf->second = bcd2bin(msf->second);
	msf->frame  = bcd2bin(msf->frame);
}