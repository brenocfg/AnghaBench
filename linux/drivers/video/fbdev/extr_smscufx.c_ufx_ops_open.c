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
struct ufx_data {int /*<<< orphan*/  fb_count; int /*<<< orphan*/  kref; scalar_t__ virtualized; } ;
struct fb_info {int /*<<< orphan*/  node; struct fb_deferred_io* fbdefio; struct ufx_data* par; } ;
struct fb_deferred_io {int /*<<< orphan*/  deferred_io; int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UFX_DEFIO_WRITE_DELAY ; 
 int /*<<< orphan*/  console ; 
 int /*<<< orphan*/  fb_deferred_io_init (struct fb_info*) ; 
 scalar_t__ fb_defio ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct fb_deferred_io* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufx_dpy_deferred_io ; 

__attribute__((used)) static int ufx_ops_open(struct fb_info *info, int user)
{
	struct ufx_data *dev = info->par;

	/* fbcon aggressively connects to first framebuffer it finds,
	 * preventing other clients (X) from working properly. Usually
	 * not what the user wants. Fail by default with option to enable. */
	if (user == 0 && !console)
		return -EBUSY;

	/* If the USB device is gone, we don't accept new opens */
	if (dev->virtualized)
		return -ENODEV;

	dev->fb_count++;

	kref_get(&dev->kref);

	if (fb_defio && (info->fbdefio == NULL)) {
		/* enable defio at last moment if not disabled by client */

		struct fb_deferred_io *fbdefio;

		fbdefio = kzalloc(sizeof(*fbdefio), GFP_KERNEL);
		if (fbdefio) {
			fbdefio->delay = UFX_DEFIO_WRITE_DELAY;
			fbdefio->deferred_io = ufx_dpy_deferred_io;
		}

		info->fbdefio = fbdefio;
		fb_deferred_io_init(info);
	}

	pr_debug("open /dev/fb%d user=%d fb_info=%p count=%d",
		info->node, user, info, dev->fb_count);

	return 0;
}