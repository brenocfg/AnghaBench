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
typedef  int /*<<< orphan*/  u32 ;
struct txbd8 {int /*<<< orphan*/  lstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_LFLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXBD_WRAP ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gfar_clear_txbd_status(struct txbd8 *bdp)
{
	u32 lstatus = be32_to_cpu(bdp->lstatus);

	lstatus &= BD_LFLAG(TXBD_WRAP);
	bdp->lstatus = cpu_to_be32(lstatus);
}