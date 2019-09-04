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
struct myri10ge_priv {char* fw_version; scalar_t__ fw_ver_major; scalar_t__ fw_ver_minor; int /*<<< orphan*/  fw_ver_tiny; TYPE_1__* pdev; } ;
struct mcp_gen_header {int /*<<< orphan*/  version; int /*<<< orphan*/  mcp_type; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MCP_TYPE_ETH ; 
 scalar_t__ MXGEFW_VERSION_MAJOR ; 
 scalar_t__ MXGEFW_VERSION_MINOR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,...) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char*,char*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
myri10ge_validate_firmware(struct myri10ge_priv *mgp,
			   struct mcp_gen_header *hdr)
{
	struct device *dev = &mgp->pdev->dev;

	/* check firmware type */
	if (ntohl(hdr->mcp_type) != MCP_TYPE_ETH) {
		dev_err(dev, "Bad firmware type: 0x%x\n", ntohl(hdr->mcp_type));
		return -EINVAL;
	}

	/* save firmware version for ethtool */
	strncpy(mgp->fw_version, hdr->version, sizeof(mgp->fw_version));
	mgp->fw_version[sizeof(mgp->fw_version) - 1] = '\0';

	sscanf(mgp->fw_version, "%d.%d.%d", &mgp->fw_ver_major,
	       &mgp->fw_ver_minor, &mgp->fw_ver_tiny);

	if (!(mgp->fw_ver_major == MXGEFW_VERSION_MAJOR &&
	      mgp->fw_ver_minor == MXGEFW_VERSION_MINOR)) {
		dev_err(dev, "Found firmware version %s\n", mgp->fw_version);
		dev_err(dev, "Driver needs %d.%d\n", MXGEFW_VERSION_MAJOR,
			MXGEFW_VERSION_MINOR);
		return -EINVAL;
	}
	return 0;
}