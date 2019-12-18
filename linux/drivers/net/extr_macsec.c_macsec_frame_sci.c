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
struct TYPE_2__ {int /*<<< orphan*/  h_source; } ;
struct macsec_eth_header {TYPE_1__ eth; int /*<<< orphan*/  secure_channel_id; } ;
typedef  int /*<<< orphan*/  sci_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACSEC_PORT_ES ; 
 int /*<<< orphan*/  make_sci (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static sci_t macsec_frame_sci(struct macsec_eth_header *hdr, bool sci_present)
{
	sci_t sci;

	if (sci_present)
		memcpy(&sci, hdr->secure_channel_id,
		       sizeof(hdr->secure_channel_id));
	else
		sci = make_sci(hdr->eth.h_source, MACSEC_PORT_ES);

	return sci;
}