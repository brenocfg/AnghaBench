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
struct sahara_dev {int flags; } ;

/* Variables and functions */
 int FLAGS_CBC ; 
 int FLAGS_ENCRYPT ; 
 int SAHARA_HDR_BASE ; 
 int SAHARA_HDR_CHA_SKHA ; 
 int SAHARA_HDR_FORM_KEY ; 
 int SAHARA_HDR_LLO ; 
 int SAHARA_HDR_PARITY_BIT ; 
 int SAHARA_HDR_SKHA_ALG_AES ; 
 int SAHARA_HDR_SKHA_MODE_CBC ; 
 int SAHARA_HDR_SKHA_OP_ENC ; 

__attribute__((used)) static u32 sahara_aes_key_hdr(struct sahara_dev *dev)
{
	u32 hdr = SAHARA_HDR_BASE | SAHARA_HDR_SKHA_ALG_AES |
			SAHARA_HDR_FORM_KEY | SAHARA_HDR_LLO |
			SAHARA_HDR_CHA_SKHA | SAHARA_HDR_PARITY_BIT;

	if (dev->flags & FLAGS_CBC) {
		hdr |= SAHARA_HDR_SKHA_MODE_CBC;
		hdr ^= SAHARA_HDR_PARITY_BIT;
	}

	if (dev->flags & FLAGS_ENCRYPT) {
		hdr |= SAHARA_HDR_SKHA_OP_ENC;
		hdr ^= SAHARA_HDR_PARITY_BIT;
	}

	return hdr;
}