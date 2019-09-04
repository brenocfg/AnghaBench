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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
#define  BLKSECTSET 194 
#define  CDROMCLOSETRAY 193 
#define  CDROMEJECT 192 
#define  CDROMEJECT_SW 191 
#define  CDROMMULTISESSION 190 
#define  CDROMPAUSE 189 
#define  CDROMPLAYBLK 188 
#define  CDROMPLAYMSF 187 
#define  CDROMPLAYTRKIND 186 
#define  CDROMREADALL 185 
#define  CDROMREADAUDIO 184 
#define  CDROMREADCOOKED 183 
#define  CDROMREADMODE1 182 
#define  CDROMREADMODE2 181 
#define  CDROMREADRAW 180 
#define  CDROMREADTOCENTRY 179 
#define  CDROMREADTOCHDR 178 
#define  CDROMRESET 177 
#define  CDROMRESUME 176 
#define  CDROMSEEK 175 
#define  CDROMSTART 174 
#define  CDROMSTOP 173 
#define  CDROMSUBCHNL 172 
#define  CDROMVOLCTRL 171 
#define  CDROMVOLREAD 170 
#define  CDROM_CHANGER_NSLOTS 169 
#define  CDROM_CLEAR_OPTIONS 168 
#define  CDROM_DEBUG 167 
#define  CDROM_DISC_STATUS 166 
#define  CDROM_DRIVE_STATUS 165 
#define  CDROM_GET_CAPABILITY 164 
#define  CDROM_GET_MCN 163 
#define  CDROM_LOCKDOOR 162 
#define  CDROM_MEDIA_CHANGED 161 
#define  CDROM_SELECT_DISC 160 
#define  CDROM_SELECT_SPEED 159 
#define  CDROM_SEND_PACKET 158 
#define  CDROM_SET_OPTIONS 157 
#define  DVD_AUTH 156 
#define  DVD_READ_STRUCT 155 
#define  DVD_WRITE_STRUCT 154 
 int ENOIOCTLCMD ; 
#define  HDIO_DRIVE_CMD 153 
#define  HDIO_DRIVE_TASK 152 
#define  HDIO_GET_32BIT 151 
#define  HDIO_GET_ACOUSTIC 150 
#define  HDIO_GET_ADDRESS 149 
#define  HDIO_GET_BUSSTATE 148 
#define  HDIO_GET_DMA 147 
#define  HDIO_GET_IDENTITY 146 
#define  HDIO_GET_KEEPSETTINGS 145 
#define  HDIO_GET_MULTCOUNT 144 
#define  HDIO_GET_NICE 143 
#define  HDIO_GET_NOWERR 142 
#define  HDIO_GET_UNMASKINTR 141 
#define  HDIO_GET_WCACHE 140 
#define  HDIO_SET_32BIT 139 
#define  HDIO_SET_ACOUSTIC 138 
#define  HDIO_SET_ADDRESS 137 
#define  HDIO_SET_BUSSTATE 136 
#define  HDIO_SET_DMA 135 
#define  HDIO_SET_KEEPSETTINGS 134 
#define  HDIO_SET_MULTCOUNT 133 
#define  HDIO_SET_NICE 132 
#define  HDIO_SET_NOWERR 131 
#define  HDIO_SET_PIO_MODE 130 
#define  HDIO_SET_UNMASKINTR 129 
#define  HDIO_SET_WCACHE 128 
 int __blkdev_driver_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int compat_cdrom_generic_command (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int compat_cdrom_read_audio (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int compat_hdio_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 scalar_t__ compat_ptr (unsigned long) ; 

__attribute__((used)) static int compat_blkdev_driver_ioctl(struct block_device *bdev, fmode_t mode,
			unsigned cmd, unsigned long arg)
{
	switch (cmd) {
	case HDIO_GET_UNMASKINTR:
	case HDIO_GET_MULTCOUNT:
	case HDIO_GET_KEEPSETTINGS:
	case HDIO_GET_32BIT:
	case HDIO_GET_NOWERR:
	case HDIO_GET_DMA:
	case HDIO_GET_NICE:
	case HDIO_GET_WCACHE:
	case HDIO_GET_ACOUSTIC:
	case HDIO_GET_ADDRESS:
	case HDIO_GET_BUSSTATE:
		return compat_hdio_ioctl(bdev, mode, cmd, arg);
	case CDROMREADAUDIO:
		return compat_cdrom_read_audio(bdev, mode, cmd, arg);
	case CDROM_SEND_PACKET:
		return compat_cdrom_generic_command(bdev, mode, cmd, arg);

	/*
	 * No handler required for the ones below, we just need to
	 * convert arg to a 64 bit pointer.
	 */
	case BLKSECTSET:
	/*
	 * 0x03 -- HD/IDE ioctl's used by hdparm and friends.
	 *         Some need translations, these do not.
	 */
	case HDIO_GET_IDENTITY:
	case HDIO_DRIVE_TASK:
	case HDIO_DRIVE_CMD:
	/* 0x330 is reserved -- it used to be HDIO_GETGEO_BIG */
	case 0x330:
	/* CDROM stuff */
	case CDROMPAUSE:
	case CDROMRESUME:
	case CDROMPLAYMSF:
	case CDROMPLAYTRKIND:
	case CDROMREADTOCHDR:
	case CDROMREADTOCENTRY:
	case CDROMSTOP:
	case CDROMSTART:
	case CDROMEJECT:
	case CDROMVOLCTRL:
	case CDROMSUBCHNL:
	case CDROMMULTISESSION:
	case CDROM_GET_MCN:
	case CDROMRESET:
	case CDROMVOLREAD:
	case CDROMSEEK:
	case CDROMPLAYBLK:
	case CDROMCLOSETRAY:
	case CDROM_DISC_STATUS:
	case CDROM_CHANGER_NSLOTS:
	case CDROM_GET_CAPABILITY:
	/* Ignore cdrom.h about these next 5 ioctls, they absolutely do
	 * not take a struct cdrom_read, instead they take a struct cdrom_msf
	 * which is compatible.
	 */
	case CDROMREADMODE2:
	case CDROMREADMODE1:
	case CDROMREADRAW:
	case CDROMREADCOOKED:
	case CDROMREADALL:
	/* DVD ioctls */
	case DVD_READ_STRUCT:
	case DVD_WRITE_STRUCT:
	case DVD_AUTH:
		arg = (unsigned long)compat_ptr(arg);
	/* These intepret arg as an unsigned long, not as a pointer,
	 * so we must not do compat_ptr() conversion. */
	case HDIO_SET_MULTCOUNT:
	case HDIO_SET_UNMASKINTR:
	case HDIO_SET_KEEPSETTINGS:
	case HDIO_SET_32BIT:
	case HDIO_SET_NOWERR:
	case HDIO_SET_DMA:
	case HDIO_SET_PIO_MODE:
	case HDIO_SET_NICE:
	case HDIO_SET_WCACHE:
	case HDIO_SET_ACOUSTIC:
	case HDIO_SET_BUSSTATE:
	case HDIO_SET_ADDRESS:
	case CDROMEJECT_SW:
	case CDROM_SET_OPTIONS:
	case CDROM_CLEAR_OPTIONS:
	case CDROM_SELECT_SPEED:
	case CDROM_SELECT_DISC:
	case CDROM_MEDIA_CHANGED:
	case CDROM_DRIVE_STATUS:
	case CDROM_LOCKDOOR:
	case CDROM_DEBUG:
		break;
	default:
		/* unknown ioctl number */
		return -ENOIOCTLCMD;
	}

	return __blkdev_driver_ioctl(bdev, mode, cmd, arg);
}