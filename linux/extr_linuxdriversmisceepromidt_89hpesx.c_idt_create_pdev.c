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
struct idt_89hpesx_dev {scalar_t__ iniccode; int /*<<< orphan*/  csr; int /*<<< orphan*/  inicsrcmd; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  flags; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CCODE_PEC ; 
 int /*<<< orphan*/  CSR_DEF ; 
 int /*<<< orphan*/  CSR_DWE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct idt_89hpesx_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLIENT_PEC ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_PEC ; 
 struct idt_89hpesx_dev* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct idt_89hpesx_dev*) ; 
 int /*<<< orphan*/  idt_get_fw_data (struct idt_89hpesx_dev*) ; 

__attribute__((used)) static struct idt_89hpesx_dev *idt_create_pdev(struct i2c_client *client)
{
	struct idt_89hpesx_dev *pdev;

	/* Allocate memory for driver data */
	pdev = devm_kmalloc(&client->dev, sizeof(struct idt_89hpesx_dev),
		GFP_KERNEL);
	if (pdev == NULL)
		return ERR_PTR(-ENOMEM);

	/* Initialize basic fields of the data */
	pdev->client = client;
	i2c_set_clientdata(client, pdev);

	/* Read firmware nodes information */
	idt_get_fw_data(pdev);

	/* Initialize basic CSR CMD field - use full DWORD-sized r/w ops */
	pdev->inicsrcmd = CSR_DWE;
	pdev->csr = CSR_DEF;

	/* Enable Packet Error Checking if it's supported by adapter */
	if (i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_PEC)) {
		pdev->iniccode = CCODE_PEC;
		client->flags |= I2C_CLIENT_PEC;
	} else /* PEC is unsupported */ {
		pdev->iniccode = 0;
	}

	return pdev;
}