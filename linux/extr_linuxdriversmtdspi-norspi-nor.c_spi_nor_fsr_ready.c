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
struct spi_nor {int /*<<< orphan*/  (* write_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int FSR_E_ERR ; 
 int FSR_PT_ERR ; 
 int FSR_P_ERR ; 
 int FSR_READY ; 
 int /*<<< orphan*/  SPINOR_OP_CLFSR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int read_fsr (struct spi_nor*) ; 
 int /*<<< orphan*/  stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int spi_nor_fsr_ready(struct spi_nor *nor)
{
	int fsr = read_fsr(nor);
	if (fsr < 0)
		return fsr;

	if (fsr & (FSR_E_ERR | FSR_P_ERR)) {
		if (fsr & FSR_E_ERR)
			dev_err(nor->dev, "Erase operation failed.\n");
		else
			dev_err(nor->dev, "Program operation failed.\n");

		if (fsr & FSR_PT_ERR)
			dev_err(nor->dev,
			"Attempted to modify a protected sector.\n");

		nor->write_reg(nor, SPINOR_OP_CLFSR, NULL, 0);
		return -EIO;
	}

	return fsr & FSR_READY;
}