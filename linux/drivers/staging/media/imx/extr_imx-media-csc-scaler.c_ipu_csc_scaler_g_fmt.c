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
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; int /*<<< orphan*/  type; } ;
struct ipu_csc_scaler_q_data {int /*<<< orphan*/  cur_fmt; } ;
struct ipu_csc_scaler_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct ipu_csc_scaler_ctx* fh_to_ctx (void*) ; 
 struct ipu_csc_scaler_q_data* get_q_data (struct ipu_csc_scaler_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipu_csc_scaler_g_fmt(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct ipu_csc_scaler_ctx *ctx = fh_to_ctx(priv);
	struct ipu_csc_scaler_q_data *q_data;

	q_data = get_q_data(ctx, f->type);

	f->fmt.pix = q_data->cur_fmt;

	return 0;
}