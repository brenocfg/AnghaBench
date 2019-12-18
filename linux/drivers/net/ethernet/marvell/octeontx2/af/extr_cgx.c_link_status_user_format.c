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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct cgx_link_user_info {size_t link_up; size_t full_duplex; size_t lmac_type_id; int /*<<< orphan*/  lmac_type; int /*<<< orphan*/  speed; } ;
struct cgx {int dummy; } ;

/* Variables and functions */
 size_t FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LMACTYPE_STR_LEN ; 
 int /*<<< orphan*/  RESP_LINKSTAT_FDUPLEX ; 
 int /*<<< orphan*/  RESP_LINKSTAT_SPEED ; 
 int /*<<< orphan*/  RESP_LINKSTAT_UP ; 
 size_t cgx_get_lmac_type (struct cgx*,int /*<<< orphan*/ ) ; 
 char** cgx_lmactype_string ; 
 int /*<<< orphan*/ * cgx_speed_mbps ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static inline void link_status_user_format(u64 lstat,
					   struct cgx_link_user_info *linfo,
					   struct cgx *cgx, u8 lmac_id)
{
	char *lmac_string;

	linfo->link_up = FIELD_GET(RESP_LINKSTAT_UP, lstat);
	linfo->full_duplex = FIELD_GET(RESP_LINKSTAT_FDUPLEX, lstat);
	linfo->speed = cgx_speed_mbps[FIELD_GET(RESP_LINKSTAT_SPEED, lstat)];
	linfo->lmac_type_id = cgx_get_lmac_type(cgx, lmac_id);
	lmac_string = cgx_lmactype_string[linfo->lmac_type_id];
	strncpy(linfo->lmac_type, lmac_string, LMACTYPE_STR_LEN - 1);
}