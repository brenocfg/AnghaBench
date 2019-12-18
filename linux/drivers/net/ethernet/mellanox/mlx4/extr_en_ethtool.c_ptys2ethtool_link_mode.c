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
struct ptys2ethtool_config {unsigned long* supported; unsigned long* advertised; } ;
typedef  enum ethtool_report { ____Placeholder_ethtool_report } ethtool_report ;

/* Variables and functions */
#define  ADVERTISED 129 
#define  SUPPORTED 128 

__attribute__((used)) static unsigned long *ptys2ethtool_link_mode(struct ptys2ethtool_config *cfg,
					     enum ethtool_report report)
{
	switch (report) {
	case SUPPORTED:
		return cfg->supported;
	case ADVERTISED:
		return cfg->advertised;
	}
	return NULL;
}