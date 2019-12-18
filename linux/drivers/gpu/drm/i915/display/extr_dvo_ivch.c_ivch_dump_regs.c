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
typedef  int /*<<< orphan*/  u16 ;
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR00 ; 
 int /*<<< orphan*/  VR01 ; 
 int /*<<< orphan*/  VR10 ; 
 int /*<<< orphan*/  VR30 ; 
 int /*<<< orphan*/  VR40 ; 
 int /*<<< orphan*/  VR80 ; 
 int /*<<< orphan*/  VR81 ; 
 int /*<<< orphan*/  VR82 ; 
 int /*<<< orphan*/  VR83 ; 
 int /*<<< orphan*/  VR84 ; 
 int /*<<< orphan*/  VR85 ; 
 int /*<<< orphan*/  VR86 ; 
 int /*<<< orphan*/  VR87 ; 
 int /*<<< orphan*/  VR88 ; 
 int /*<<< orphan*/  VR8E ; 
 int /*<<< orphan*/  VR8F ; 
 int /*<<< orphan*/  ivch_read (struct intel_dvo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ivch_dump_regs(struct intel_dvo_device *dvo)
{
	u16 val;

	ivch_read(dvo, VR00, &val);
	DRM_DEBUG_KMS("VR00: 0x%04x\n", val);
	ivch_read(dvo, VR01, &val);
	DRM_DEBUG_KMS("VR01: 0x%04x\n", val);
	ivch_read(dvo, VR10, &val);
	DRM_DEBUG_KMS("VR10: 0x%04x\n", val);
	ivch_read(dvo, VR30, &val);
	DRM_DEBUG_KMS("VR30: 0x%04x\n", val);
	ivch_read(dvo, VR40, &val);
	DRM_DEBUG_KMS("VR40: 0x%04x\n", val);

	/* GPIO registers */
	ivch_read(dvo, VR80, &val);
	DRM_DEBUG_KMS("VR80: 0x%04x\n", val);
	ivch_read(dvo, VR81, &val);
	DRM_DEBUG_KMS("VR81: 0x%04x\n", val);
	ivch_read(dvo, VR82, &val);
	DRM_DEBUG_KMS("VR82: 0x%04x\n", val);
	ivch_read(dvo, VR83, &val);
	DRM_DEBUG_KMS("VR83: 0x%04x\n", val);
	ivch_read(dvo, VR84, &val);
	DRM_DEBUG_KMS("VR84: 0x%04x\n", val);
	ivch_read(dvo, VR85, &val);
	DRM_DEBUG_KMS("VR85: 0x%04x\n", val);
	ivch_read(dvo, VR86, &val);
	DRM_DEBUG_KMS("VR86: 0x%04x\n", val);
	ivch_read(dvo, VR87, &val);
	DRM_DEBUG_KMS("VR87: 0x%04x\n", val);
	ivch_read(dvo, VR88, &val);
	DRM_DEBUG_KMS("VR88: 0x%04x\n", val);

	/* Scratch register 0 - AIM Panel type */
	ivch_read(dvo, VR8E, &val);
	DRM_DEBUG_KMS("VR8E: 0x%04x\n", val);

	/* Scratch register 1 - Status register */
	ivch_read(dvo, VR8F, &val);
	DRM_DEBUG_KMS("VR8F: 0x%04x\n", val);
}