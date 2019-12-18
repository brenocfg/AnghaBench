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
struct onenand_chip {int /*<<< orphan*/  write_bufferram; int /*<<< orphan*/  read_bufferram; int /*<<< orphan*/  command; int /*<<< orphan*/  unlock_all; int /*<<< orphan*/  bbt_wait; int /*<<< orphan*/  wait; int /*<<< orphan*/  write_word; int /*<<< orphan*/  read_word; int /*<<< orphan*/  chip_probe; } ;
struct mtd_info {struct onenand_chip* priv; } ;
struct TYPE_2__ {scalar_t__ type; void* cmd_map; int /*<<< orphan*/  mem_addr; struct mtd_info* mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ TYPE_S3C6400 ; 
 scalar_t__ TYPE_S3C6410 ; 
 scalar_t__ TYPE_S5PC110 ; 
 TYPE_1__* onenand ; 
 int /*<<< orphan*/  onenand_read_bufferram ; 
 int /*<<< orphan*/  onenand_write_bufferram ; 
 int /*<<< orphan*/  s3c6400_mem_addr ; 
 int /*<<< orphan*/  s3c6410_mem_addr ; 
 void* s3c64xx_cmd_map ; 
 int /*<<< orphan*/  s3c_onenand_bbt_wait ; 
 int /*<<< orphan*/  s3c_onenand_command ; 
 int /*<<< orphan*/  s3c_onenand_readw ; 
 int /*<<< orphan*/  s3c_onenand_wait ; 
 int /*<<< orphan*/  s3c_onenand_writew ; 
 int /*<<< orphan*/  s3c_unlock_all ; 
 int /*<<< orphan*/  s5pc110_chip_probe ; 
 int /*<<< orphan*/  s5pc110_read_bufferram ; 

__attribute__((used)) static void s3c_onenand_setup(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;

	onenand->mtd = mtd;

	if (onenand->type == TYPE_S3C6400) {
		onenand->mem_addr = s3c6400_mem_addr;
		onenand->cmd_map = s3c64xx_cmd_map;
	} else if (onenand->type == TYPE_S3C6410) {
		onenand->mem_addr = s3c6410_mem_addr;
		onenand->cmd_map = s3c64xx_cmd_map;
	} else if (onenand->type == TYPE_S5PC110) {
		/* Use generic onenand functions */
		this->read_bufferram = s5pc110_read_bufferram;
		this->chip_probe = s5pc110_chip_probe;
		return;
	} else {
		BUG();
	}

	this->read_word = s3c_onenand_readw;
	this->write_word = s3c_onenand_writew;

	this->wait = s3c_onenand_wait;
	this->bbt_wait = s3c_onenand_bbt_wait;
	this->unlock_all = s3c_unlock_all;
	this->command = s3c_onenand_command;

	this->read_bufferram = onenand_read_bufferram;
	this->write_bufferram = onenand_write_bufferram;
}