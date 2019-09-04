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
struct ipu_soc {int /*<<< orphan*/  dev; } ;
struct ipu_ic_priv {struct ipu_soc* ipu; } ;
struct ipu_ic {struct ipu_ic_priv* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int calc_resize_coeffs(struct ipu_ic *ic,
			      u32 in_size, u32 out_size,
			      u32 *resize_coeff,
			      u32 *downsize_coeff)
{
	struct ipu_ic_priv *priv = ic->priv;
	struct ipu_soc *ipu = priv->ipu;
	u32 temp_size, temp_downsize;

	/*
	 * Input size cannot be more than 4096, and output size cannot
	 * be more than 1024
	 */
	if (in_size > 4096) {
		dev_err(ipu->dev, "Unsupported resize (in_size > 4096)\n");
		return -EINVAL;
	}
	if (out_size > 1024) {
		dev_err(ipu->dev, "Unsupported resize (out_size > 1024)\n");
		return -EINVAL;
	}

	/* Cannot downsize more than 4:1 */
	if ((out_size << 2) < in_size) {
		dev_err(ipu->dev, "Unsupported downsize\n");
		return -EINVAL;
	}

	/* Compute downsizing coefficient */
	temp_downsize = 0;
	temp_size = in_size;
	while (((temp_size > 1024) || (temp_size >= out_size * 2)) &&
	       (temp_downsize < 2)) {
		temp_size >>= 1;
		temp_downsize++;
	}
	*downsize_coeff = temp_downsize;

	/*
	 * compute resizing coefficient using the following equation:
	 * resize_coeff = M * (SI - 1) / (SO - 1)
	 * where M = 2^13, SI = input size, SO = output size
	 */
	*resize_coeff = (8192L * (temp_size - 1)) / (out_size - 1);
	if (*resize_coeff >= 16384L) {
		dev_err(ipu->dev, "Warning! Overflow on resize coeff.\n");
		*resize_coeff = 0x3FFF;
	}

	return 0;
}