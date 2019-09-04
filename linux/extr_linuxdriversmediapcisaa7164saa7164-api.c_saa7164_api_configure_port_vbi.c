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
typedef  int /*<<< orphan*/  u32 ;
struct tmComResVBIFormatDescrHeader {scalar_t__ bNumLines; scalar_t__ FieldRate; scalar_t__ EndLine; scalar_t__ StartLine; scalar_t__ VideoStandard; scalar_t__ bFormatIndex; } ;
struct TYPE_2__ {int buffercount; scalar_t__ BARLocation; } ;
struct saa7164_port {scalar_t__ nr; TYPE_1__ hwcfg; scalar_t__ bufptr64; scalar_t__ bufptr32h; scalar_t__ bufptr32l; scalar_t__ bufoffset; scalar_t__ bufsize; scalar_t__ pitch; scalar_t__ bufcounter; struct tmComResVBIFormatDescrHeader vbi_fmt_ntsc; } ;
struct saa7164_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGLVL_API ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int saa7164_api_configure_port_vbi(struct saa7164_dev *dev,
					  struct saa7164_port *port)
{
	struct tmComResVBIFormatDescrHeader *fmt = &port->vbi_fmt_ntsc;

	dprintk(DBGLVL_API, "    bFormatIndex  = 0x%x\n", fmt->bFormatIndex);
	dprintk(DBGLVL_API, "    VideoStandard = 0x%x\n", fmt->VideoStandard);
	dprintk(DBGLVL_API, "    StartLine     = %d\n", fmt->StartLine);
	dprintk(DBGLVL_API, "    EndLine       = %d\n", fmt->EndLine);
	dprintk(DBGLVL_API, "    FieldRate     = %d\n", fmt->FieldRate);
	dprintk(DBGLVL_API, "    bNumLines     = %d\n", fmt->bNumLines);

	/* Cache the hardware configuration in the port */

	port->bufcounter = port->hwcfg.BARLocation;
	port->pitch = port->hwcfg.BARLocation + (2 * sizeof(u32));
	port->bufsize = port->hwcfg.BARLocation + (3 * sizeof(u32));
	port->bufoffset = port->hwcfg.BARLocation + (4 * sizeof(u32));
	port->bufptr32l = port->hwcfg.BARLocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * port->hwcfg.buffercount) + sizeof(u32);
	port->bufptr32h = port->hwcfg.BARLocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * port->hwcfg.buffercount);
	port->bufptr64 = port->hwcfg.BARLocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * port->hwcfg.buffercount);
	dprintk(DBGLVL_API, "   = port->hwcfg.BARLocation = 0x%x\n",
		port->hwcfg.BARLocation);

	dprintk(DBGLVL_API, "   = VS_FORMAT_VBI (becomes dev->en[%d])\n",
		port->nr);

	return 0;
}