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
typedef  int u8 ;

/* Variables and functions */
#define  CAPI_CONF 131 
#define  CAPI_IND 130 
#define  CAPI_REQ 129 
#define  CAPI_RESP 128 

__attribute__((used)) static inline int capi_subcmd_valid(u8 subcmd)
{
	switch (subcmd) {
	case CAPI_REQ:
	case CAPI_CONF:
	case CAPI_IND:
	case CAPI_RESP:
		return 1;
	}
	return 0;
}