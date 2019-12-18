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
typedef  int u64 ;
struct cgx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGXX_CMRX_CFG ; 
 int CGX_LMAC_TYPE_MASK ; 
 int CGX_LMAC_TYPE_SHIFT ; 
 int cgx_read (struct cgx*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 cgx_get_lmac_type(struct cgx *cgx, int lmac_id)
{
	u64 cfg;

	cfg = cgx_read(cgx, lmac_id, CGXX_CMRX_CFG);
	return (cfg >> CGX_LMAC_TYPE_SHIFT) & CGX_LMAC_TYPE_MASK;
}