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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  code; } ;
struct m5mols_resolution {int type; int /*<<< orphan*/  reg; scalar_t__ height; scalar_t__ width; } ;
typedef  enum m5mols_restype { ____Placeholder_m5mols_restype } m5mols_restype ;

/* Variables and functions */
 int ARRAY_SIZE (struct m5mols_resolution*) ; 
 int EINVAL ; 
 int __find_restype (int /*<<< orphan*/ ) ; 
 int abs (scalar_t__) ; 
 struct m5mols_resolution* m5mols_reg_res ; 

__attribute__((used)) static int __find_resolution(struct v4l2_subdev *sd,
			     struct v4l2_mbus_framefmt *mf,
			     enum m5mols_restype *type,
			     u32 *resolution)
{
	const struct m5mols_resolution *fsize = &m5mols_reg_res[0];
	const struct m5mols_resolution *match = NULL;
	enum m5mols_restype stype = __find_restype(mf->code);
	int i = ARRAY_SIZE(m5mols_reg_res);
	unsigned int min_err = ~0;

	while (i--) {
		int err;
		if (stype == fsize->type) {
			err = abs(fsize->width - mf->width)
				+ abs(fsize->height - mf->height);

			if (err < min_err) {
				min_err = err;
				match = fsize;
			}
		}
		fsize++;
	}
	if (match) {
		mf->width  = match->width;
		mf->height = match->height;
		*resolution = match->reg;
		*type = stype;
		return 0;
	}

	return -EINVAL;
}