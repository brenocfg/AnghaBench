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
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIL164_FREQ_HI ; 
 int /*<<< orphan*/  SIL164_FREQ_LO ; 
 int /*<<< orphan*/  SIL164_REG8 ; 
 int /*<<< orphan*/  SIL164_REG9 ; 
 int /*<<< orphan*/  SIL164_REGC ; 
 int /*<<< orphan*/  sil164_readb (struct intel_dvo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sil164_dump_regs(struct intel_dvo_device *dvo)
{
	u8 val;

	sil164_readb(dvo, SIL164_FREQ_LO, &val);
	DRM_DEBUG_KMS("SIL164_FREQ_LO: 0x%02x\n", val);
	sil164_readb(dvo, SIL164_FREQ_HI, &val);
	DRM_DEBUG_KMS("SIL164_FREQ_HI: 0x%02x\n", val);
	sil164_readb(dvo, SIL164_REG8, &val);
	DRM_DEBUG_KMS("SIL164_REG8: 0x%02x\n", val);
	sil164_readb(dvo, SIL164_REG9, &val);
	DRM_DEBUG_KMS("SIL164_REG9: 0x%02x\n", val);
	sil164_readb(dvo, SIL164_REGC, &val);
	DRM_DEBUG_KMS("SIL164_REGC: 0x%02x\n", val);
}