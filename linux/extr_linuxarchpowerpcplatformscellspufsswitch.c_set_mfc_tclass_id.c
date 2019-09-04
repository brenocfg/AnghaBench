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
struct spu_state {int dummy; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eieio () ; 
 int /*<<< orphan*/  spu_mfc_tclass_id_set (struct spu*,int) ; 

__attribute__((used)) static inline void set_mfc_tclass_id(struct spu_state *csa, struct spu *spu)
{
	/* Save, Step 26:
	 * Restore, Step 23.
	 *     Write the MFC_TCLASS_ID register with
	 *     the value 0x10000000.
	 */
	spu_mfc_tclass_id_set(spu, 0x10000000);
	eieio();
}