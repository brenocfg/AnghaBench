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
struct i2c_algo_pca_data {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DEB2 (char*,int /*<<< orphan*/ ) ; 
 int I2C_PCA_CON_SI ; 
 int I2C_PCA_CON_STA ; 
 int I2C_PCA_CON_STO ; 
 int /*<<< orphan*/  I2C_PCA_DAT ; 
 int pca_get_con (struct i2c_algo_pca_data*) ; 
 int /*<<< orphan*/  pca_outw (struct i2c_algo_pca_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pca_set_con (struct i2c_algo_pca_data*,int) ; 
 int pca_wait (struct i2c_algo_pca_data*) ; 

__attribute__((used)) static int pca_tx_byte(struct i2c_algo_pca_data *adap,
		       __u8 b)
{
	int sta = pca_get_con(adap);
	DEB2("=== WRITE %#04x\n", b);
	pca_outw(adap, I2C_PCA_DAT, b);

	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_STA|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);

	return pca_wait(adap);
}