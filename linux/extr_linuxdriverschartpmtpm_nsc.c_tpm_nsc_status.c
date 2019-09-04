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
struct tpm_nsc_priv {scalar_t__ base; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ NSC_STATUS ; 
 struct tpm_nsc_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 

__attribute__((used)) static u8 tpm_nsc_status(struct tpm_chip *chip)
{
	struct tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);

	return inb(priv->base + NSC_STATUS);
}