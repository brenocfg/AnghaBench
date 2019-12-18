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
struct i2c_algo_pca_data {scalar_t__ chip; int /*<<< orphan*/  data; int /*<<< orphan*/  (* reset_chip ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ I2C_PCA_CHIP_9665 ; 
 int /*<<< orphan*/  I2C_PCA_IND ; 
 int /*<<< orphan*/  I2C_PCA_INDPTR ; 
 int I2C_PCA_IPRESET ; 
 int /*<<< orphan*/  pca_outw (struct i2c_algo_pca_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pca_reset(struct i2c_algo_pca_data *adap)
{
	if (adap->chip == I2C_PCA_CHIP_9665) {
		/* Ignore the reset function from the module,
		 * we can use the parallel bus reset.
		 */
		pca_outw(adap, I2C_PCA_INDPTR, I2C_PCA_IPRESET);
		pca_outw(adap, I2C_PCA_IND, 0xA5);
		pca_outw(adap, I2C_PCA_IND, 0x5A);
	} else {
		adap->reset_chip(adap->data);
	}
}