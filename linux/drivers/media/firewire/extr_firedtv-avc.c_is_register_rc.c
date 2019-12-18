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
struct avc_response_frame {scalar_t__ opcode; scalar_t__* operand; } ;

/* Variables and functions */
 scalar_t__ AVC_OPCODE_VENDOR ; 
 scalar_t__ SFE_VENDOR_DE_COMPANYID_0 ; 
 scalar_t__ SFE_VENDOR_DE_COMPANYID_1 ; 
 scalar_t__ SFE_VENDOR_DE_COMPANYID_2 ; 
 scalar_t__ SFE_VENDOR_OPCODE_REGISTER_REMOTE_CONTROL ; 

__attribute__((used)) static bool is_register_rc(struct avc_response_frame *r)
{
	return r->opcode     == AVC_OPCODE_VENDOR &&
	       r->operand[0] == SFE_VENDOR_DE_COMPANYID_0 &&
	       r->operand[1] == SFE_VENDOR_DE_COMPANYID_1 &&
	       r->operand[2] == SFE_VENDOR_DE_COMPANYID_2 &&
	       r->operand[3] == SFE_VENDOR_OPCODE_REGISTER_REMOTE_CONTROL;
}