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
struct i2c_msg {int flags; int /*<<< orphan*/  addr; } ;
struct i2c_algo_pca_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB2 (char*,int /*<<< orphan*/ ,char,int) ; 
 int I2C_M_RD ; 
 int I2C_PCA_CON_SI ; 
 int I2C_PCA_CON_STA ; 
 int I2C_PCA_CON_STO ; 
 int /*<<< orphan*/  I2C_PCA_DAT ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int pca_get_con (struct i2c_algo_pca_data*) ; 
 int /*<<< orphan*/  pca_outw (struct i2c_algo_pca_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pca_set_con (struct i2c_algo_pca_data*,int) ; 
 int pca_wait (struct i2c_algo_pca_data*) ; 

__attribute__((used)) static int pca_address(struct i2c_algo_pca_data *adap,
		       struct i2c_msg *msg)
{
	int sta = pca_get_con(adap);
	int addr = i2c_8bit_addr_from_msg(msg);

	DEB2("=== SLAVE ADDRESS %#04x+%c=%#04x\n",
	     msg->addr, msg->flags & I2C_M_RD ? 'R' : 'W', addr);

	pca_outw(adap, I2C_PCA_DAT, addr);

	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_STA|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);

	return pca_wait(adap);
}