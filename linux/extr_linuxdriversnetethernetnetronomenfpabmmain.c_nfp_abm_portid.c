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
typedef  int u32 ;
typedef  enum nfp_repr_type { ____Placeholder_nfp_repr_type } nfp_repr_type ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  NFP_ABM_PORTID_ID ; 
 int /*<<< orphan*/  NFP_ABM_PORTID_TYPE ; 

__attribute__((used)) static u32 nfp_abm_portid(enum nfp_repr_type rtype, unsigned int id)
{
	return FIELD_PREP(NFP_ABM_PORTID_TYPE, rtype) |
	       FIELD_PREP(NFP_ABM_PORTID_ID, id);
}