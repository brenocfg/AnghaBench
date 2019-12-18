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
struct tegra_hsp_channel {struct tegra_hsp* hsp; scalar_t__ regs; } ;
struct tegra_hsp_doorbell {unsigned int master; unsigned int index; struct tegra_hsp_channel channel; int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;
struct tegra_hsp {int num_sm; int num_ss; int num_as; int /*<<< orphan*/  lock; int /*<<< orphan*/  doorbells; int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct tegra_hsp_channel* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SZ_64K ; 
 int /*<<< orphan*/  devm_kstrdup_const (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct tegra_hsp_doorbell* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct tegra_hsp_channel *
tegra_hsp_doorbell_create(struct tegra_hsp *hsp, const char *name,
			  unsigned int master, unsigned int index)
{
	struct tegra_hsp_doorbell *db;
	unsigned int offset;
	unsigned long flags;

	db = devm_kzalloc(hsp->dev, sizeof(*db), GFP_KERNEL);
	if (!db)
		return ERR_PTR(-ENOMEM);

	offset = (1 + (hsp->num_sm / 2) + hsp->num_ss + hsp->num_as) * SZ_64K;
	offset += index * 0x100;

	db->channel.regs = hsp->regs + offset;
	db->channel.hsp = hsp;

	db->name = devm_kstrdup_const(hsp->dev, name, GFP_KERNEL);
	db->master = master;
	db->index = index;

	spin_lock_irqsave(&hsp->lock, flags);
	list_add_tail(&db->list, &hsp->doorbells);
	spin_unlock_irqrestore(&hsp->lock, flags);

	return &db->channel;
}