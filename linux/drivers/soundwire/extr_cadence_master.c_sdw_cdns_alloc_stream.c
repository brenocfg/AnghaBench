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
typedef  scalar_t__ u32 ;
struct sdw_cdns_streams {int /*<<< orphan*/  bd; int /*<<< orphan*/  num_bd; int /*<<< orphan*/  out; int /*<<< orphan*/  num_out; int /*<<< orphan*/  in; int /*<<< orphan*/  num_in; } ;
struct sdw_cdns_port {struct sdw_cdns_pdi* pdi; } ;
struct sdw_cdns_pdi {scalar_t__ ch_count; scalar_t__ dir; scalar_t__ h_ch_num; scalar_t__ l_ch_num; } ;
struct sdw_cdns {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ SDW_DATA_DIR_RX ; 
 struct sdw_cdns_pdi* cdns_find_pdi (struct sdw_cdns*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sdw_cdns_alloc_stream(struct sdw_cdns *cdns,
			  struct sdw_cdns_streams *stream,
			  struct sdw_cdns_port *port, u32 ch, u32 dir)
{
	struct sdw_cdns_pdi *pdi = NULL;

	if (dir == SDW_DATA_DIR_RX)
		pdi = cdns_find_pdi(cdns, stream->num_in, stream->in);
	else
		pdi = cdns_find_pdi(cdns, stream->num_out, stream->out);

	/* check if we found a PDI, else find in bi-directional */
	if (!pdi)
		pdi = cdns_find_pdi(cdns, stream->num_bd, stream->bd);

	if (!pdi)
		return -EIO;

	port->pdi = pdi;
	pdi->l_ch_num = 0;
	pdi->h_ch_num = ch - 1;
	pdi->dir = dir;
	pdi->ch_count = ch;

	return 0;
}