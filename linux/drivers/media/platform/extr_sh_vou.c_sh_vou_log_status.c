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
struct sh_vou_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOUAD1R ; 
 int /*<<< orphan*/  VOUAD2R ; 
 int /*<<< orphan*/  VOUAIR ; 
 int /*<<< orphan*/  VOUBCR ; 
 int /*<<< orphan*/  VOUCR ; 
 int /*<<< orphan*/  VOUDFR ; 
 int /*<<< orphan*/  VOUDPR ; 
 int /*<<< orphan*/  VOUDSR ; 
 int /*<<< orphan*/  VOUER ; 
 int /*<<< orphan*/  VOUHIR ; 
 int /*<<< orphan*/  VOUIR ; 
 int /*<<< orphan*/  VOUISR ; 
 int /*<<< orphan*/  VOUMSR ; 
 int /*<<< orphan*/  VOURCR ; 
 int /*<<< orphan*/  VOURPR ; 
 int /*<<< orphan*/  VOUSRR ; 
 int /*<<< orphan*/  VOUSTR ; 
 int /*<<< orphan*/  VOUSWR ; 
 int /*<<< orphan*/  VOUVCR ; 
 int /*<<< orphan*/  VOUVPR ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_vou_reg_a_read (struct sh_vou_device*,int /*<<< orphan*/ ) ; 
 struct sh_vou_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int sh_vou_log_status(struct file *file, void *priv)
{
	struct sh_vou_device *vou_dev = video_drvdata(file);

	pr_info("VOUER:   0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUER));
	pr_info("VOUCR:   0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUCR));
	pr_info("VOUSTR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUSTR));
	pr_info("VOUVCR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUVCR));
	pr_info("VOUISR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUISR));
	pr_info("VOUBCR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUBCR));
	pr_info("VOUDPR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUDPR));
	pr_info("VOUDSR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUDSR));
	pr_info("VOUVPR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUVPR));
	pr_info("VOUIR:   0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUIR));
	pr_info("VOUSRR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUSRR));
	pr_info("VOUMSR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUMSR));
	pr_info("VOUHIR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUHIR));
	pr_info("VOUDFR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUDFR));
	pr_info("VOUAD1R: 0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUAD1R));
	pr_info("VOUAD2R: 0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUAD2R));
	pr_info("VOUAIR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUAIR));
	pr_info("VOUSWR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOUSWR));
	pr_info("VOURCR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOURCR));
	pr_info("VOURPR:  0x%08x\n", sh_vou_reg_a_read(vou_dev, VOURPR));
	return 0;
}