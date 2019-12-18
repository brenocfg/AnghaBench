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
struct tb_switch {int /*<<< orphan*/  dev; } ;
struct nvmem_device {int dummy; } ;
struct nvmem_config {char* name; int read_only; int root_only; int id; int stride; int word_size; size_t size; struct tb_switch* priv; int /*<<< orphan*/  owner; int /*<<< orphan*/ * dev; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  memset (struct nvmem_config*,int /*<<< orphan*/ ,int) ; 
 struct nvmem_device* nvmem_register (struct nvmem_config*) ; 
 int /*<<< orphan*/  tb_switch_nvm_read ; 
 int /*<<< orphan*/  tb_switch_nvm_write ; 

__attribute__((used)) static struct nvmem_device *register_nvmem(struct tb_switch *sw, int id,
					   size_t size, bool active)
{
	struct nvmem_config config;

	memset(&config, 0, sizeof(config));

	if (active) {
		config.name = "nvm_active";
		config.reg_read = tb_switch_nvm_read;
		config.read_only = true;
	} else {
		config.name = "nvm_non_active";
		config.reg_write = tb_switch_nvm_write;
		config.root_only = true;
	}

	config.id = id;
	config.stride = 4;
	config.word_size = 4;
	config.size = size;
	config.dev = &sw->dev;
	config.owner = THIS_MODULE;
	config.priv = sw;

	return nvmem_register(&config);
}