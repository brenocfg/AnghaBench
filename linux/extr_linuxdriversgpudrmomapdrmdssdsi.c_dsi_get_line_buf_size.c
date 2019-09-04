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
struct dsi_data {TYPE_1__* data; } ;
struct TYPE_2__ {int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSI_GNQ ; 
 int DSI_QUIRK_GNQ ; 
 int REG_GET (struct dsi_data*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static unsigned int dsi_get_line_buf_size(struct dsi_data *dsi)
{
	int val;

	/* line buffer on OMAP3 is 1024 x 24bits */
	/* XXX: for some reason using full buffer size causes
	 * considerable TX slowdown with update sizes that fill the
	 * whole buffer */
	if (!(dsi->data->quirks & DSI_QUIRK_GNQ))
		return 1023 * 3;

	val = REG_GET(dsi, DSI_GNQ, 14, 12); /* VP1_LINE_BUFFER_SIZE */

	switch (val) {
	case 1:
		return 512 * 3;		/* 512x24 bits */
	case 2:
		return 682 * 3;		/* 682x24 bits */
	case 3:
		return 853 * 3;		/* 853x24 bits */
	case 4:
		return 1024 * 3;	/* 1024x24 bits */
	case 5:
		return 1194 * 3;	/* 1194x24 bits */
	case 6:
		return 1365 * 3;	/* 1365x24 bits */
	case 7:
		return 1920 * 3;	/* 1920x24 bits */
	default:
		BUG();
		return 0;
	}
}