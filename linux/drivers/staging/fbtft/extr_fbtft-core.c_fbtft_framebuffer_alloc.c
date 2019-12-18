#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_14__ {unsigned int width; unsigned int height; scalar_t__ regwidth; scalar_t__ buswidth; scalar_t__ backlight; scalar_t__ debug; int /*<<< orphan*/ * init_sequence; } ;
struct fbtft_platform_data {int fps; int txbuflen; char* gamma; int rotate; int /*<<< orphan*/  startbyte; int /*<<< orphan*/  bgr; TYPE_1__ display; } ;
struct TYPE_13__ {int /*<<< orphan*/  register_backlight; int /*<<< orphan*/  update_display; int /*<<< orphan*/  mkdirty; int /*<<< orphan*/  reset; int /*<<< orphan*/  set_addr_win; int /*<<< orphan*/  write_register; int /*<<< orphan*/  write_vmem; int /*<<< orphan*/  read; int /*<<< orphan*/  write; } ;
struct TYPE_12__ {int len; void* buf; } ;
struct TYPE_22__ {int num_curves; int num_values; int /*<<< orphan*/ * curves; int /*<<< orphan*/  lock; } ;
struct fbtft_par {TYPE_11__ fbtftops; TYPE_10__ txbuf; struct fb_info* info; TYPE_9__ gamma; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  const* init_sequence; int /*<<< orphan*/  startbyte; int /*<<< orphan*/  bgr; int /*<<< orphan*/  dirty_lock; void* buf; scalar_t__ debug; struct fbtft_platform_data* pdata; } ;
struct fbtft_display {int txbuflen; unsigned int bpp; unsigned int fps; char* gamma; int gamma_num; int gamma_len; unsigned int width; unsigned int height; int /*<<< orphan*/  fbtftops; scalar_t__ backlight; scalar_t__ debug; scalar_t__ regwidth; scalar_t__ buswidth; int /*<<< orphan*/ * init_sequence; } ;
struct fb_ops {int /*<<< orphan*/  fb_blank; int /*<<< orphan*/  fb_setcolreg; int /*<<< orphan*/  fb_imageblit; int /*<<< orphan*/  fb_copyarea; int /*<<< orphan*/  fb_fillrect; int /*<<< orphan*/  fb_write; int /*<<< orphan*/  fb_read; int /*<<< orphan*/  owner; } ;
struct TYPE_20__ {scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_19__ {int length; scalar_t__ offset; } ;
struct TYPE_18__ {int offset; int length; } ;
struct TYPE_17__ {int offset; int length; } ;
struct TYPE_21__ {int rotate; unsigned int xres; unsigned int yres; unsigned int xres_virtual; unsigned int yres_virtual; unsigned int bits_per_pixel; int nonstd; TYPE_7__ transp; TYPE_6__ blue; TYPE_5__ green; TYPE_4__ red; } ;
struct TYPE_16__ {unsigned int line_length; int smem_len; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ ypanstep; scalar_t__ xpanstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {int flags; struct device* device; int /*<<< orphan*/  pseudo_palette; struct fbtft_par* par; TYPE_8__ var; TYPE_3__ fix; struct fb_deferred_io* fbdefio; struct fb_ops* fbops; int /*<<< orphan*/ * screen_buffer; } ;
struct fb_deferred_io {unsigned int delay; int /*<<< orphan*/  deferred_io; } ;
struct device {TYPE_2__* driver; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  int /*<<< orphan*/  gamma_curves ;
struct TYPE_15__ {int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int FBINFO_FLAG_DEFAULT ; 
 int FBINFO_VIRTFB ; 
 int FBTFT_GAMMA_MAX_VALUES_TOTAL ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int HZ ; 
 int PAGE_SIZE ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_deferred_io_init (struct fb_info*) ; 
 int /*<<< orphan*/  fb_sys_read ; 
 int /*<<< orphan*/  fbtft_deferred_io ; 
 int /*<<< orphan*/  fbtft_expand_debug_value (scalar_t__*) ; 
 int /*<<< orphan*/  fbtft_fb_blank ; 
 int /*<<< orphan*/  fbtft_fb_copyarea ; 
 int /*<<< orphan*/  fbtft_fb_fillrect ; 
 int /*<<< orphan*/  fbtft_fb_imageblit ; 
 int /*<<< orphan*/  fbtft_fb_setcolreg ; 
 int /*<<< orphan*/  fbtft_fb_write ; 
 scalar_t__ fbtft_gamma_parse_str (struct fbtft_par*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbtft_merge_fbtftops (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fbtft_mkdirty ; 
 int /*<<< orphan*/  fbtft_read_spi ; 
 int /*<<< orphan*/  fbtft_register_backlight ; 
 int /*<<< orphan*/  fbtft_reset ; 
 int /*<<< orphan*/  fbtft_set_addr_win ; 
 int /*<<< orphan*/  fbtft_update_display ; 
 int /*<<< orphan*/  fbtft_write_reg8_bus8 ; 
 int /*<<< orphan*/  fbtft_write_spi ; 
 int /*<<< orphan*/  fbtft_write_vmem16_bus8 ; 
 struct fb_info* framebuffer_alloc (int,struct device*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

struct fb_info *fbtft_framebuffer_alloc(struct fbtft_display *display,
					struct device *dev,
					struct fbtft_platform_data *pdata)
{
	struct fb_info *info;
	struct fbtft_par *par;
	struct fb_ops *fbops = NULL;
	struct fb_deferred_io *fbdefio = NULL;
	u8 *vmem = NULL;
	void *txbuf = NULL;
	void *buf = NULL;
	unsigned int width;
	unsigned int height;
	int txbuflen = display->txbuflen;
	unsigned int bpp = display->bpp;
	unsigned int fps = display->fps;
	int vmem_size;
	const s16 *init_sequence = display->init_sequence;
	char *gamma = display->gamma;
	u32 *gamma_curves = NULL;

	/* sanity check */
	if (display->gamma_num * display->gamma_len >
			FBTFT_GAMMA_MAX_VALUES_TOTAL) {
		dev_err(dev, "FBTFT_GAMMA_MAX_VALUES_TOTAL=%d is exceeded\n",
			FBTFT_GAMMA_MAX_VALUES_TOTAL);
		return NULL;
	}

	/* defaults */
	if (!fps)
		fps = 20;
	if (!bpp)
		bpp = 16;

	if (!pdata) {
		dev_err(dev, "platform data is missing\n");
		return NULL;
	}

	/* override driver values? */
	if (pdata->fps)
		fps = pdata->fps;
	if (pdata->txbuflen)
		txbuflen = pdata->txbuflen;
	if (pdata->display.init_sequence)
		init_sequence = pdata->display.init_sequence;
	if (pdata->gamma)
		gamma = pdata->gamma;
	if (pdata->display.debug)
		display->debug = pdata->display.debug;
	if (pdata->display.backlight)
		display->backlight = pdata->display.backlight;
	if (pdata->display.width)
		display->width = pdata->display.width;
	if (pdata->display.height)
		display->height = pdata->display.height;
	if (pdata->display.buswidth)
		display->buswidth = pdata->display.buswidth;
	if (pdata->display.regwidth)
		display->regwidth = pdata->display.regwidth;

	display->debug |= debug;
	fbtft_expand_debug_value(&display->debug);

	switch (pdata->rotate) {
	case 90:
	case 270:
		width =  display->height;
		height = display->width;
		break;
	default:
		width =  display->width;
		height = display->height;
	}

	vmem_size = display->width * display->height * bpp / 8;
	vmem = vzalloc(vmem_size);
	if (!vmem)
		goto alloc_fail;

	fbops = devm_kzalloc(dev, sizeof(struct fb_ops), GFP_KERNEL);
	if (!fbops)
		goto alloc_fail;

	fbdefio = devm_kzalloc(dev, sizeof(struct fb_deferred_io), GFP_KERNEL);
	if (!fbdefio)
		goto alloc_fail;

	buf = devm_kzalloc(dev, 128, GFP_KERNEL);
	if (!buf)
		goto alloc_fail;

	if (display->gamma_num && display->gamma_len) {
		gamma_curves = devm_kcalloc(dev,
					    display->gamma_num *
					    display->gamma_len,
					    sizeof(gamma_curves[0]),
					    GFP_KERNEL);
		if (!gamma_curves)
			goto alloc_fail;
	}

	info = framebuffer_alloc(sizeof(struct fbtft_par), dev);
	if (!info)
		goto alloc_fail;

	info->screen_buffer = vmem;
	info->fbops = fbops;
	info->fbdefio = fbdefio;

	fbops->owner        =      dev->driver->owner;
	fbops->fb_read      =      fb_sys_read;
	fbops->fb_write     =      fbtft_fb_write;
	fbops->fb_fillrect  =      fbtft_fb_fillrect;
	fbops->fb_copyarea  =      fbtft_fb_copyarea;
	fbops->fb_imageblit =      fbtft_fb_imageblit;
	fbops->fb_setcolreg =      fbtft_fb_setcolreg;
	fbops->fb_blank     =      fbtft_fb_blank;

	fbdefio->delay =           HZ / fps;
	fbdefio->deferred_io =     fbtft_deferred_io;
	fb_deferred_io_init(info);

	strncpy(info->fix.id, dev->driver->name, 16);
	info->fix.type =           FB_TYPE_PACKED_PIXELS;
	info->fix.visual =         FB_VISUAL_TRUECOLOR;
	info->fix.xpanstep =	   0;
	info->fix.ypanstep =	   0;
	info->fix.ywrapstep =	   0;
	info->fix.line_length =    width * bpp / 8;
	info->fix.accel =          FB_ACCEL_NONE;
	info->fix.smem_len =       vmem_size;

	info->var.rotate =         pdata->rotate;
	info->var.xres =           width;
	info->var.yres =           height;
	info->var.xres_virtual =   info->var.xres;
	info->var.yres_virtual =   info->var.yres;
	info->var.bits_per_pixel = bpp;
	info->var.nonstd =         1;

	/* RGB565 */
	info->var.red.offset =     11;
	info->var.red.length =     5;
	info->var.green.offset =   5;
	info->var.green.length =   6;
	info->var.blue.offset =    0;
	info->var.blue.length =    5;
	info->var.transp.offset =  0;
	info->var.transp.length =  0;

	info->flags =              FBINFO_FLAG_DEFAULT | FBINFO_VIRTFB;

	par = info->par;
	par->info = info;
	par->pdata = pdata;
	par->debug = display->debug;
	par->buf = buf;
	spin_lock_init(&par->dirty_lock);
	par->bgr = pdata->bgr;
	par->startbyte = pdata->startbyte;
	par->init_sequence = init_sequence;
	par->gamma.curves = gamma_curves;
	par->gamma.num_curves = display->gamma_num;
	par->gamma.num_values = display->gamma_len;
	mutex_init(&par->gamma.lock);
	info->pseudo_palette = par->pseudo_palette;

	if (par->gamma.curves && gamma) {
		if (fbtft_gamma_parse_str(par, par->gamma.curves, gamma,
					  strlen(gamma)))
			goto release_framebuf;
	}

	/* Transmit buffer */
	if (txbuflen == -1)
		txbuflen = vmem_size + 2; /* add in case startbyte is used */
	if (txbuflen >= vmem_size + 2)
		txbuflen = 0;

#ifdef __LITTLE_ENDIAN
	if ((!txbuflen) && (bpp > 8))
		txbuflen = PAGE_SIZE; /* need buffer for byteswapping */
#endif

	if (txbuflen > 0) {
		txbuf = devm_kzalloc(par->info->device, txbuflen, GFP_KERNEL);
		if (!txbuf)
			goto release_framebuf;
		par->txbuf.buf = txbuf;
		par->txbuf.len = txbuflen;
	}

	/* default fbtft operations */
	par->fbtftops.write = fbtft_write_spi;
	par->fbtftops.read = fbtft_read_spi;
	par->fbtftops.write_vmem = fbtft_write_vmem16_bus8;
	par->fbtftops.write_register = fbtft_write_reg8_bus8;
	par->fbtftops.set_addr_win = fbtft_set_addr_win;
	par->fbtftops.reset = fbtft_reset;
	par->fbtftops.mkdirty = fbtft_mkdirty;
	par->fbtftops.update_display = fbtft_update_display;
	if (display->backlight)
		par->fbtftops.register_backlight = fbtft_register_backlight;

	/* use driver provided functions */
	fbtft_merge_fbtftops(&par->fbtftops, &display->fbtftops);

	return info;

release_framebuf:
	framebuffer_release(info);

alloc_fail:
	vfree(vmem);

	return NULL;
}