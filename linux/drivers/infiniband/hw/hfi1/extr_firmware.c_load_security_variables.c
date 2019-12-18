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
struct hfi1_devdata {int dummy; } ;
struct firmware_details {scalar_t__ css_header; int /*<<< orphan*/  mu; int /*<<< orphan*/  r2; int /*<<< orphan*/  modulus; } ;
struct css_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_SIZE ; 
 int /*<<< orphan*/  MISC_CFG_RSA_MODULUS ; 
 int /*<<< orphan*/  MISC_CFG_RSA_MU ; 
 int /*<<< orphan*/  MISC_CFG_RSA_R2 ; 
 int /*<<< orphan*/  MISC_CFG_SHA_PRELOAD ; 
 int /*<<< orphan*/  MU_SIZE ; 
 int /*<<< orphan*/  write_rsa_data (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_streamed_rsa_data (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void load_security_variables(struct hfi1_devdata *dd,
				    struct firmware_details *fdet)
{
	/* Security variables a.  Write the modulus */
	write_rsa_data(dd, MISC_CFG_RSA_MODULUS, fdet->modulus, KEY_SIZE);
	/* Security variables b.  Write the r2 */
	write_rsa_data(dd, MISC_CFG_RSA_R2, fdet->r2, KEY_SIZE);
	/* Security variables c.  Write the mu */
	write_rsa_data(dd, MISC_CFG_RSA_MU, fdet->mu, MU_SIZE);
	/* Security variables d.  Write the header */
	write_streamed_rsa_data(dd, MISC_CFG_SHA_PRELOAD,
				(u8 *)fdet->css_header,
				sizeof(struct css_header));
}