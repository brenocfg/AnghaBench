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

/* Variables and functions */
 int I2C_PCA_CON_AA ; 
 int I2C_PCA_CON_SI ; 
 int I2C_PCA_CON_STA ; 
 int I2C_PCA_CON_STO ; 
 int pca_get_con (struct i2c_algo_pca_data*) ; 
 int /*<<< orphan*/  pca_set_con (struct i2c_algo_pca_data*,int) ; 
 int pca_wait (struct i2c_algo_pca_data*) ; 

__attribute__((used)) static int pca_rx_ack(struct i2c_algo_pca_data *adap,
		      int ack)
{
	int sta = pca_get_con(adap);

	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_STA|I2C_PCA_CON_SI|I2C_PCA_CON_AA);

	if (ack)
		sta |= I2C_PCA_CON_AA;

	pca_set_con(adap, sta);
	return pca_wait(adap);
}