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
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct tpm_atmel_priv {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATML_STATUS_ABORT ; 
 struct tpm_atmel_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tpm_atml_cancel(struct tpm_chip *chip)
{
	struct tpm_atmel_priv *priv = dev_get_drvdata(&chip->dev);

	iowrite8(ATML_STATUS_ABORT, priv->iobase + 1);
}