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
struct r820t_sect_type {int gain_x; int /*<<< orphan*/  phase_y; } ;
struct r820t_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r820t_compre_cor (struct r820t_sect_type*) ; 
 int r820t_iq_tree (struct r820t_priv*,struct r820t_sect_type*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r820t_section(struct r820t_priv *priv,
			 struct r820t_sect_type *iq_point)
{
	int rc;
	struct r820t_sect_type compare_iq[3], compare_bet[3];

	/* Try X-1 column and save min result to compare_bet[0] */
	if (!(iq_point->gain_x & 0x1f))
		compare_iq[0].gain_x = ((iq_point->gain_x) & 0xdf) + 1;  /* Q-path, Gain=1 */
	else
		compare_iq[0].gain_x  = iq_point->gain_x - 1;  /* left point */
	compare_iq[0].phase_y = iq_point->phase_y;

	/* y-direction */
	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
			compare_iq[0].phase_y, 0x08);
	if (rc < 0)
		return rc;

	r820t_compre_cor(compare_iq);

	compare_bet[0] = compare_iq[0];

	/* Try X column and save min result to compare_bet[1] */
	compare_iq[0].gain_x  = iq_point->gain_x;
	compare_iq[0].phase_y = iq_point->phase_y;

	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
			   compare_iq[0].phase_y, 0x08);
	if (rc < 0)
		return rc;

	r820t_compre_cor(compare_iq);

	compare_bet[1] = compare_iq[0];

	/* Try X+1 column and save min result to compare_bet[2] */
	if ((iq_point->gain_x & 0x1f) == 0x00)
		compare_iq[0].gain_x = ((iq_point->gain_x) | 0x20) + 1;  /* I-path, Gain=1 */
	else
		compare_iq[0].gain_x = iq_point->gain_x + 1;
	compare_iq[0].phase_y = iq_point->phase_y;

	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
			   compare_iq[0].phase_y, 0x08);
	if (rc < 0)
		return rc;

	r820t_compre_cor(compare_iq);

	compare_bet[2] = compare_iq[0];

	r820t_compre_cor(compare_bet);

	*iq_point = compare_bet[0];

	return 0;
}