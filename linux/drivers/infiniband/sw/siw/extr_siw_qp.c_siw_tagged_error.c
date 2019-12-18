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
typedef  enum ddp_ecode { ____Placeholder_ddp_ecode } ddp_ecode ;

/* Variables and functions */
 int DDP_ECODE_T_BASE_BOUNDS ; 
 int DDP_ECODE_T_INVALID_STAG ; 
 int DDP_ECODE_T_STAG_NOT_ASSOC ; 
#define  E_ACCESS_PERM 131 
#define  E_BASE_BOUNDS 130 
#define  E_PD_MISMATCH 129 
#define  E_STAG_INVALID 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

enum ddp_ecode siw_tagged_error(enum siw_access_state state)
{
	switch (state) {
	case E_STAG_INVALID:
		return DDP_ECODE_T_INVALID_STAG;
	case E_BASE_BOUNDS:
		return DDP_ECODE_T_BASE_BOUNDS;
	case E_PD_MISMATCH:
		return DDP_ECODE_T_STAG_NOT_ASSOC;
	case E_ACCESS_PERM:
		/*
		 * RFC 5041 (DDP) lacks an ecode for insufficient access
		 * permissions. 'Invalid STag' seem to be the closest
		 * match though.
		 */
		return DDP_ECODE_T_INVALID_STAG;
	default:
		WARN_ON(1);
		return DDP_ECODE_T_INVALID_STAG;
	}
}