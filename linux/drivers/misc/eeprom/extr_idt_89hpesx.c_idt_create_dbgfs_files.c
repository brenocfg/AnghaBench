#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct idt_89hpesx_dev {int /*<<< orphan*/  csr_dir; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  name; TYPE_1__* adapter; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int nr; } ;

/* Variables and functions */
 int CSRNAME_LEN ; 
 int /*<<< orphan*/  csr_dbgdir ; 
 int /*<<< orphan*/  csr_dbgfs_ops ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct idt_89hpesx_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idt_create_dbgfs_files(struct idt_89hpesx_dev *pdev)
{
	struct i2c_client *cli = pdev->client;
	char fname[CSRNAME_LEN];

	/* Create Debugfs directory for CSR file */
	snprintf(fname, CSRNAME_LEN, "%d-%04hx", cli->adapter->nr, cli->addr);
	pdev->csr_dir = debugfs_create_dir(fname, csr_dbgdir);

	/* Create Debugfs file for CSR read/write operations */
	debugfs_create_file(cli->name, 0600, pdev->csr_dir, pdev,
			    &csr_dbgfs_ops);
}