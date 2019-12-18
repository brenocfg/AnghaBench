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
typedef  enum siw_access_state { ____Placeholder_siw_access_state } siw_access_state ;
typedef  enum rdmap_ecode { ____Placeholder_rdmap_ecode } rdmap_ecode ;

/* Variables and functions */
#define  E_ACCESS_PERM 131 
#define  E_BASE_BOUNDS 130 
#define  E_PD_MISMATCH 129 
#define  E_STAG_INVALID 128 
 int RDMAP_ECODE_ACCESS_RIGHTS ; 
 int RDMAP_ECODE_BASE_BOUNDS ; 
 int RDMAP_ECODE_INVALID_STAG ; 
 int RDMAP_ECODE_STAG_NOT_ASSOC ; 
 int RDMAP_ECODE_UNSPECIFIED ; 

enum rdmap_ecode siw_rdmap_error(enum siw_access_state state)
{
	switch (state) {
	case E_STAG_INVALID:
		return RDMAP_ECODE_INVALID_STAG;
	case E_BASE_BOUNDS:
		return RDMAP_ECODE_BASE_BOUNDS;
	case E_PD_MISMATCH:
		return RDMAP_ECODE_STAG_NOT_ASSOC;
	case E_ACCESS_PERM:
		return RDMAP_ECODE_ACCESS_RIGHTS;
	default:
		return RDMAP_ECODE_UNSPECIFIED;
	}
}