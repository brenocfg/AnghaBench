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

/* Variables and functions */
 int /*<<< orphan*/  MACSEC_SCI_LEN ; 
 unsigned int MACSEC_TAG_LEN ; 

__attribute__((used)) static unsigned int macsec_sectag_len(bool sci_present)
{
	return MACSEC_TAG_LEN + (sci_present ? MACSEC_SCI_LEN : 0);
}