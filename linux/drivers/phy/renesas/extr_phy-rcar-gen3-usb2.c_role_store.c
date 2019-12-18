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
struct rcar_gen3_chan {int /*<<< orphan*/  is_otg_channel; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 int PHY_MODE_USB_DEVICE ; 
 int PHY_MODE_USB_HOST ; 
 struct rcar_gen3_chan* dev_get_drvdata (struct device*) ; 
 int rcar_gen3_check_id (struct rcar_gen3_chan*) ; 
 int rcar_gen3_get_phy_mode (struct rcar_gen3_chan*) ; 
 int /*<<< orphan*/  rcar_gen3_init_for_a_peri (struct rcar_gen3_chan*) ; 
 int /*<<< orphan*/  rcar_gen3_init_for_b_host (struct rcar_gen3_chan*) ; 
 int /*<<< orphan*/  rcar_gen3_init_for_peri (struct rcar_gen3_chan*) ; 
 int /*<<< orphan*/  rcar_gen3_init_from_a_peri_to_a_host (struct rcar_gen3_chan*) ; 
 int /*<<< orphan*/  rcar_gen3_is_any_rphy_initialized (struct rcar_gen3_chan*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t role_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct rcar_gen3_chan *ch = dev_get_drvdata(dev);
	bool is_b_device;
	enum phy_mode cur_mode, new_mode;

	if (!ch->is_otg_channel || !rcar_gen3_is_any_rphy_initialized(ch))
		return -EIO;

	if (!strncmp(buf, "host", strlen("host")))
		new_mode = PHY_MODE_USB_HOST;
	else if (!strncmp(buf, "peripheral", strlen("peripheral")))
		new_mode = PHY_MODE_USB_DEVICE;
	else
		return -EINVAL;

	/* is_b_device: true is B-Device. false is A-Device. */
	is_b_device = rcar_gen3_check_id(ch);
	cur_mode = rcar_gen3_get_phy_mode(ch);

	/* If current and new mode is the same, this returns the error */
	if (cur_mode == new_mode)
		return -EINVAL;

	if (new_mode == PHY_MODE_USB_HOST) { /* And is_host must be false */
		if (!is_b_device)	/* A-Peripheral */
			rcar_gen3_init_from_a_peri_to_a_host(ch);
		else			/* B-Peripheral */
			rcar_gen3_init_for_b_host(ch);
	} else {			/* And is_host must be true */
		if (!is_b_device)	/* A-Host */
			rcar_gen3_init_for_a_peri(ch);
		else			/* B-Host */
			rcar_gen3_init_for_peri(ch);
	}

	return count;
}