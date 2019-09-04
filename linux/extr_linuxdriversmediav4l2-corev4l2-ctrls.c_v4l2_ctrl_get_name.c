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
typedef  int u32 ;

/* Variables and functions */
#define  V4L2_CID_3A_LOCK 455 
#define  V4L2_CID_ALPHA_COMPONENT 454 
#define  V4L2_CID_ANALOGUE_GAIN 453 
#define  V4L2_CID_AUDIO_BALANCE 452 
#define  V4L2_CID_AUDIO_BASS 451 
#define  V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME 450 
#define  V4L2_CID_AUDIO_COMPRESSION_ENABLED 449 
#define  V4L2_CID_AUDIO_COMPRESSION_GAIN 448 
#define  V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME 447 
#define  V4L2_CID_AUDIO_COMPRESSION_THRESHOLD 446 
#define  V4L2_CID_AUDIO_LIMITER_DEVIATION 445 
#define  V4L2_CID_AUDIO_LIMITER_ENABLED 444 
#define  V4L2_CID_AUDIO_LIMITER_RELEASE_TIME 443 
#define  V4L2_CID_AUDIO_LOUDNESS 442 
#define  V4L2_CID_AUDIO_MUTE 441 
#define  V4L2_CID_AUDIO_TREBLE 440 
#define  V4L2_CID_AUDIO_VOLUME 439 
#define  V4L2_CID_AUTOBRIGHTNESS 438 
#define  V4L2_CID_AUTOGAIN 437 
#define  V4L2_CID_AUTO_EXPOSURE_BIAS 436 
#define  V4L2_CID_AUTO_FOCUS_RANGE 435 
#define  V4L2_CID_AUTO_FOCUS_START 434 
#define  V4L2_CID_AUTO_FOCUS_STATUS 433 
#define  V4L2_CID_AUTO_FOCUS_STOP 432 
#define  V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE 431 
#define  V4L2_CID_AUTO_WHITE_BALANCE 430 
#define  V4L2_CID_BACKLIGHT_COMPENSATION 429 
#define  V4L2_CID_BAND_STOP_FILTER 428 
#define  V4L2_CID_BG_COLOR 427 
#define  V4L2_CID_BLACK_LEVEL 426 
#define  V4L2_CID_BLUE_BALANCE 425 
#define  V4L2_CID_BRIGHTNESS 424 
#define  V4L2_CID_CAMERA_CLASS 423 
#define  V4L2_CID_CHROMA_AGC 422 
#define  V4L2_CID_CHROMA_GAIN 421 
#define  V4L2_CID_COLORFX 420 
#define  V4L2_CID_COLORFX_CBCR 419 
#define  V4L2_CID_COLOR_KILLER 418 
#define  V4L2_CID_CONTRAST 417 
#define  V4L2_CID_DEINTERLACING_MODE 416 
#define  V4L2_CID_DETECT_CLASS 415 
#define  V4L2_CID_DETECT_MD_GLOBAL_THRESHOLD 414 
#define  V4L2_CID_DETECT_MD_MODE 413 
#define  V4L2_CID_DETECT_MD_REGION_GRID 412 
#define  V4L2_CID_DETECT_MD_THRESHOLD_GRID 411 
#define  V4L2_CID_DIGITAL_GAIN 410 
#define  V4L2_CID_DO_WHITE_BALANCE 409 
#define  V4L2_CID_DV_CLASS 408 
#define  V4L2_CID_DV_RX_IT_CONTENT_TYPE 407 
#define  V4L2_CID_DV_RX_POWER_PRESENT 406 
#define  V4L2_CID_DV_RX_RGB_RANGE 405 
#define  V4L2_CID_DV_TX_EDID_PRESENT 404 
#define  V4L2_CID_DV_TX_HOTPLUG 403 
#define  V4L2_CID_DV_TX_IT_CONTENT_TYPE 402 
#define  V4L2_CID_DV_TX_MODE 401 
#define  V4L2_CID_DV_TX_RGB_RANGE 400 
#define  V4L2_CID_DV_TX_RXSENSE 399 
#define  V4L2_CID_EXPOSURE 398 
#define  V4L2_CID_EXPOSURE_ABSOLUTE 397 
#define  V4L2_CID_EXPOSURE_AUTO 396 
#define  V4L2_CID_EXPOSURE_AUTO_PRIORITY 395 
#define  V4L2_CID_EXPOSURE_METERING 394 
#define  V4L2_CID_FLASH_CHARGE 393 
#define  V4L2_CID_FLASH_CLASS 392 
#define  V4L2_CID_FLASH_FAULT 391 
#define  V4L2_CID_FLASH_INDICATOR_INTENSITY 390 
#define  V4L2_CID_FLASH_INTENSITY 389 
#define  V4L2_CID_FLASH_LED_MODE 388 
#define  V4L2_CID_FLASH_READY 387 
#define  V4L2_CID_FLASH_STROBE 386 
#define  V4L2_CID_FLASH_STROBE_SOURCE 385 
#define  V4L2_CID_FLASH_STROBE_STATUS 384 
#define  V4L2_CID_FLASH_STROBE_STOP 383 
#define  V4L2_CID_FLASH_TIMEOUT 382 
#define  V4L2_CID_FLASH_TORCH_INTENSITY 381 
#define  V4L2_CID_FM_RX_CLASS 380 
#define  V4L2_CID_FM_TX_CLASS 379 
#define  V4L2_CID_FOCUS_ABSOLUTE 378 
#define  V4L2_CID_FOCUS_AUTO 377 
#define  V4L2_CID_FOCUS_RELATIVE 376 
#define  V4L2_CID_GAIN 375 
#define  V4L2_CID_GAMMA 374 
#define  V4L2_CID_HBLANK 373 
#define  V4L2_CID_HFLIP 372 
#define  V4L2_CID_HUE 371 
#define  V4L2_CID_HUE_AUTO 370 
#define  V4L2_CID_ILLUMINATORS_1 369 
#define  V4L2_CID_ILLUMINATORS_2 368 
#define  V4L2_CID_IMAGE_PROC_CLASS 367 
#define  V4L2_CID_IMAGE_SOURCE_CLASS 366 
#define  V4L2_CID_IMAGE_STABILIZATION 365 
#define  V4L2_CID_IRIS_ABSOLUTE 364 
#define  V4L2_CID_IRIS_RELATIVE 363 
#define  V4L2_CID_ISO_SENSITIVITY 362 
#define  V4L2_CID_ISO_SENSITIVITY_AUTO 361 
#define  V4L2_CID_JPEG_ACTIVE_MARKER 360 
#define  V4L2_CID_JPEG_CHROMA_SUBSAMPLING 359 
#define  V4L2_CID_JPEG_CLASS 358 
#define  V4L2_CID_JPEG_COMPRESSION_QUALITY 357 
#define  V4L2_CID_JPEG_RESTART_INTERVAL 356 
#define  V4L2_CID_LINK_FREQ 355 
#define  V4L2_CID_MIN_BUFFERS_FOR_CAPTURE 354 
#define  V4L2_CID_MIN_BUFFERS_FOR_OUTPUT 353 
#define  V4L2_CID_MPEG_AUDIO_AAC_BITRATE 352 
#define  V4L2_CID_MPEG_AUDIO_AC3_BITRATE 351 
#define  V4L2_CID_MPEG_AUDIO_CRC 350 
#define  V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK 349 
#define  V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK 348 
#define  V4L2_CID_MPEG_AUDIO_EMPHASIS 347 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 346 
#define  V4L2_CID_MPEG_AUDIO_L1_BITRATE 345 
#define  V4L2_CID_MPEG_AUDIO_L2_BITRATE 344 
#define  V4L2_CID_MPEG_AUDIO_L3_BITRATE 343 
#define  V4L2_CID_MPEG_AUDIO_MODE 342 
#define  V4L2_CID_MPEG_AUDIO_MODE_EXTENSION 341 
#define  V4L2_CID_MPEG_AUDIO_MUTE 340 
#define  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 339 
#define  V4L2_CID_MPEG_CLASS 338 
#define  V4L2_CID_MPEG_STREAM_PES_ID_AUDIO 337 
#define  V4L2_CID_MPEG_STREAM_PES_ID_VIDEO 336 
#define  V4L2_CID_MPEG_STREAM_PID_AUDIO 335 
#define  V4L2_CID_MPEG_STREAM_PID_PCR 334 
#define  V4L2_CID_MPEG_STREAM_PID_PMT 333 
#define  V4L2_CID_MPEG_STREAM_PID_VIDEO 332 
#define  V4L2_CID_MPEG_STREAM_TYPE 331 
#define  V4L2_CID_MPEG_STREAM_VBI_FMT 330 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 329 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 328 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 327 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 326 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 325 
#define  V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB 324 
#define  V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER 323 
#define  V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE 322 
#define  V4L2_CID_MPEG_VIDEO_DEC_FRAME 321 
#define  V4L2_CID_MPEG_VIDEO_DEC_PTS 320 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 319 
#define  V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME 318 
#define  V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE 317 
#define  V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 316 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 315 
#define  V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP 314 
#define  V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP 313 
#define  V4L2_CID_MPEG_VIDEO_H263_MAX_QP 312 
#define  V4L2_CID_MPEG_VIDEO_H263_MIN_QP 311 
#define  V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP 310 
#define  V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM 309 
#define  V4L2_CID_MPEG_VIDEO_H264_ASO 308 
#define  V4L2_CID_MPEG_VIDEO_H264_ASO_SLICE_ORDER 307 
#define  V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP 306 
#define  V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE 305 
#define  V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE 304 
#define  V4L2_CID_MPEG_VIDEO_H264_FMO 303 
#define  V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_DIRECTION 302 
#define  V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_RATE 301 
#define  V4L2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE 300 
#define  V4L2_CID_MPEG_VIDEO_H264_FMO_RUN_LENGTH 299 
#define  V4L2_CID_MPEG_VIDEO_H264_FMO_SLICE_GROUP 298 
#define  V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING 297 
#define  V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER 296 
#define  V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER_QP 295 
#define  V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_TYPE 294 
#define  V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP 293 
#define  V4L2_CID_MPEG_VIDEO_H264_I_PERIOD 292 
#define  V4L2_CID_MPEG_VIDEO_H264_LEVEL 291 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA 290 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA 289 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE 288 
#define  V4L2_CID_MPEG_VIDEO_H264_MAX_QP 287 
#define  V4L2_CID_MPEG_VIDEO_H264_MIN_QP 286 
#define  V4L2_CID_MPEG_VIDEO_H264_PROFILE 285 
#define  V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP 284 
#define  V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE 283 
#define  V4L2_CID_MPEG_VIDEO_H264_SEI_FP_CURRENT_FRAME_0 282 
#define  V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING 281 
#define  V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT 280 
#define  V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH 279 
#define  V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE 278 
#define  V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC 277 
#define  V4L2_CID_MPEG_VIDEO_HEADER_MODE 276 
#define  V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP 275 
#define  V4L2_CID_MPEG_VIDEO_HEVC_CONST_INTRA_PRED 274 
#define  V4L2_CID_MPEG_VIDEO_HEVC_FRAME_RATE_RESOLUTION 273 
#define  V4L2_CID_MPEG_VIDEO_HEVC_GENERAL_PB 272 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_BR 271 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_QP 270 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_BR 269 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_QP 268 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_BR 267 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_QP 266 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_BR 265 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_QP 264 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_BR 263 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_QP 262 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_BR 261 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_QP 260 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_BR 259 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_QP 258 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_LAYER 257 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE 256 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_QP 255 
#define  V4L2_CID_MPEG_VIDEO_HEVC_INTRA_PU_SPLIT 254 
#define  V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP 253 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LEVEL 252 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LF_BETA_OFFSET_DIV2 251 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LF_TC_OFFSET_DIV2 250 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE 249 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LOSSLESS_CU 248 
#define  V4L2_CID_MPEG_VIDEO_HEVC_MAX_NUM_MERGE_MV_MINUS1 247 
#define  V4L2_CID_MPEG_VIDEO_HEVC_MAX_PARTITION_DEPTH 246 
#define  V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP 245 
#define  V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP 244 
#define  V4L2_CID_MPEG_VIDEO_HEVC_PROFILE 243 
#define  V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP 242 
#define  V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_PERIOD 241 
#define  V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE 240 
#define  V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD 239 
#define  V4L2_CID_MPEG_VIDEO_HEVC_STRONG_SMOOTHING 238 
#define  V4L2_CID_MPEG_VIDEO_HEVC_TEMPORAL_ID 237 
#define  V4L2_CID_MPEG_VIDEO_HEVC_TIER 236 
#define  V4L2_CID_MPEG_VIDEO_HEVC_TMV_PREDICTION 235 
#define  V4L2_CID_MPEG_VIDEO_HEVC_WAVEFRONT 234 
#define  V4L2_CID_MPEG_VIDEO_HEVC_WITHOUT_STARTCODE 233 
#define  V4L2_CID_MPEG_VIDEO_MAX_REF_PIC 232 
#define  V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE 231 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP 230 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP 229 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL 228 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP 227 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP 226 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE 225 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP 224 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_QPEL 223 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES 222 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB 221 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE 220 
#define  V4L2_CID_MPEG_VIDEO_MUTE 219 
#define  V4L2_CID_MPEG_VIDEO_MUTE_YUV 218 
#define  V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE 217 
#define  V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE 216 
#define  V4L2_CID_MPEG_VIDEO_PREPEND_SPSPPS_TO_IDR 215 
#define  V4L2_CID_MPEG_VIDEO_PULLDOWN 214 
#define  V4L2_CID_MPEG_VIDEO_REF_NUMBER_FOR_PFRAMES 213 
#define  V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER 212 
#define  V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION 211 
#define  V4L2_CID_MPEG_VIDEO_VBV_DELAY 210 
#define  V4L2_CID_MPEG_VIDEO_VBV_SIZE 209 
#define  V4L2_CID_MPEG_VIDEO_VP8_PROFILE 208 
#define  V4L2_CID_MPEG_VIDEO_VP9_PROFILE 207 
#define  V4L2_CID_MPEG_VIDEO_VPX_FILTER_LEVEL 206 
#define  V4L2_CID_MPEG_VIDEO_VPX_FILTER_SHARPNESS 205 
#define  V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_REF_PERIOD 204 
#define  V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL 203 
#define  V4L2_CID_MPEG_VIDEO_VPX_IMD_DISABLE_4X4 202 
#define  V4L2_CID_MPEG_VIDEO_VPX_I_FRAME_QP 201 
#define  V4L2_CID_MPEG_VIDEO_VPX_MAX_QP 200 
#define  V4L2_CID_MPEG_VIDEO_VPX_MIN_QP 199 
#define  V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS 198 
#define  V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES 197 
#define  V4L2_CID_MPEG_VIDEO_VPX_P_FRAME_QP 196 
#define  V4L2_CID_PAN_ABSOLUTE 195 
#define  V4L2_CID_PAN_RELATIVE 194 
#define  V4L2_CID_PAN_RESET 193 
#define  V4L2_CID_PAN_SPEED 192 
#define  V4L2_CID_PILOT_TONE_DEVIATION 191 
#define  V4L2_CID_PILOT_TONE_ENABLED 190 
#define  V4L2_CID_PILOT_TONE_FREQUENCY 189 
#define  V4L2_CID_PIXEL_RATE 188 
#define  V4L2_CID_POWER_LINE_FREQUENCY 187 
#define  V4L2_CID_PRIVACY 186 
#define  V4L2_CID_RDS_RECEPTION 185 
#define  V4L2_CID_RDS_RX_MUSIC_SPEECH 184 
#define  V4L2_CID_RDS_RX_PS_NAME 183 
#define  V4L2_CID_RDS_RX_PTY 182 
#define  V4L2_CID_RDS_RX_RADIO_TEXT 181 
#define  V4L2_CID_RDS_RX_TRAFFIC_ANNOUNCEMENT 180 
#define  V4L2_CID_RDS_RX_TRAFFIC_PROGRAM 179 
#define  V4L2_CID_RDS_TX_ALT_FREQS 178 
#define  V4L2_CID_RDS_TX_ALT_FREQS_ENABLE 177 
#define  V4L2_CID_RDS_TX_ARTIFICIAL_HEAD 176 
#define  V4L2_CID_RDS_TX_COMPRESSED 175 
#define  V4L2_CID_RDS_TX_DEVIATION 174 
#define  V4L2_CID_RDS_TX_DYNAMIC_PTY 173 
#define  V4L2_CID_RDS_TX_MONO_STEREO 172 
#define  V4L2_CID_RDS_TX_MUSIC_SPEECH 171 
#define  V4L2_CID_RDS_TX_PI 170 
#define  V4L2_CID_RDS_TX_PS_NAME 169 
#define  V4L2_CID_RDS_TX_PTY 168 
#define  V4L2_CID_RDS_TX_RADIO_TEXT 167 
#define  V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT 166 
#define  V4L2_CID_RDS_TX_TRAFFIC_PROGRAM 165 
#define  V4L2_CID_RED_BALANCE 164 
#define  V4L2_CID_RF_TUNER_BANDWIDTH 163 
#define  V4L2_CID_RF_TUNER_BANDWIDTH_AUTO 162 
#define  V4L2_CID_RF_TUNER_CLASS 161 
#define  V4L2_CID_RF_TUNER_IF_GAIN 160 
#define  V4L2_CID_RF_TUNER_IF_GAIN_AUTO 159 
#define  V4L2_CID_RF_TUNER_LNA_GAIN 158 
#define  V4L2_CID_RF_TUNER_LNA_GAIN_AUTO 157 
#define  V4L2_CID_RF_TUNER_MIXER_GAIN 156 
#define  V4L2_CID_RF_TUNER_MIXER_GAIN_AUTO 155 
#define  V4L2_CID_RF_TUNER_PLL_LOCK 154 
#define  V4L2_CID_RF_TUNER_RF_GAIN 153 
#define  V4L2_CID_ROTATE 152 
#define  V4L2_CID_SATURATION 151 
#define  V4L2_CID_SCENE_MODE 150 
#define  V4L2_CID_SHARPNESS 149 
#define  V4L2_CID_TEST_PATTERN 148 
#define  V4L2_CID_TEST_PATTERN_BLUE 147 
#define  V4L2_CID_TEST_PATTERN_GREENB 146 
#define  V4L2_CID_TEST_PATTERN_GREENR 145 
#define  V4L2_CID_TEST_PATTERN_RED 144 
#define  V4L2_CID_TILT_ABSOLUTE 143 
#define  V4L2_CID_TILT_RELATIVE 142 
#define  V4L2_CID_TILT_RESET 141 
#define  V4L2_CID_TILT_SPEED 140 
#define  V4L2_CID_TUNE_ANTENNA_CAPACITOR 139 
#define  V4L2_CID_TUNE_DEEMPHASIS 138 
#define  V4L2_CID_TUNE_POWER_LEVEL 137 
#define  V4L2_CID_TUNE_PREEMPHASIS 136 
#define  V4L2_CID_USER_CLASS 135 
#define  V4L2_CID_VBLANK 134 
#define  V4L2_CID_VFLIP 133 
#define  V4L2_CID_WHITE_BALANCE_TEMPERATURE 132 
#define  V4L2_CID_WIDE_DYNAMIC_RANGE 131 
#define  V4L2_CID_ZOOM_ABSOLUTE 130 
#define  V4L2_CID_ZOOM_CONTINUOUS 129 
#define  V4L2_CID_ZOOM_RELATIVE 128 

const char *v4l2_ctrl_get_name(u32 id)
{
	switch (id) {
	/* USER controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	case V4L2_CID_USER_CLASS:		return "User Controls";
	case V4L2_CID_BRIGHTNESS:		return "Brightness";
	case V4L2_CID_CONTRAST:			return "Contrast";
	case V4L2_CID_SATURATION:		return "Saturation";
	case V4L2_CID_HUE:			return "Hue";
	case V4L2_CID_AUDIO_VOLUME:		return "Volume";
	case V4L2_CID_AUDIO_BALANCE:		return "Balance";
	case V4L2_CID_AUDIO_BASS:		return "Bass";
	case V4L2_CID_AUDIO_TREBLE:		return "Treble";
	case V4L2_CID_AUDIO_MUTE:		return "Mute";
	case V4L2_CID_AUDIO_LOUDNESS:		return "Loudness";
	case V4L2_CID_BLACK_LEVEL:		return "Black Level";
	case V4L2_CID_AUTO_WHITE_BALANCE:	return "White Balance, Automatic";
	case V4L2_CID_DO_WHITE_BALANCE:		return "Do White Balance";
	case V4L2_CID_RED_BALANCE:		return "Red Balance";
	case V4L2_CID_BLUE_BALANCE:		return "Blue Balance";
	case V4L2_CID_GAMMA:			return "Gamma";
	case V4L2_CID_EXPOSURE:			return "Exposure";
	case V4L2_CID_AUTOGAIN:			return "Gain, Automatic";
	case V4L2_CID_GAIN:			return "Gain";
	case V4L2_CID_HFLIP:			return "Horizontal Flip";
	case V4L2_CID_VFLIP:			return "Vertical Flip";
	case V4L2_CID_POWER_LINE_FREQUENCY:	return "Power Line Frequency";
	case V4L2_CID_HUE_AUTO:			return "Hue, Automatic";
	case V4L2_CID_WHITE_BALANCE_TEMPERATURE: return "White Balance Temperature";
	case V4L2_CID_SHARPNESS:		return "Sharpness";
	case V4L2_CID_BACKLIGHT_COMPENSATION:	return "Backlight Compensation";
	case V4L2_CID_CHROMA_AGC:		return "Chroma AGC";
	case V4L2_CID_COLOR_KILLER:		return "Color Killer";
	case V4L2_CID_COLORFX:			return "Color Effects";
	case V4L2_CID_AUTOBRIGHTNESS:		return "Brightness, Automatic";
	case V4L2_CID_BAND_STOP_FILTER:		return "Band-Stop Filter";
	case V4L2_CID_ROTATE:			return "Rotate";
	case V4L2_CID_BG_COLOR:			return "Background Color";
	case V4L2_CID_CHROMA_GAIN:		return "Chroma Gain";
	case V4L2_CID_ILLUMINATORS_1:		return "Illuminator 1";
	case V4L2_CID_ILLUMINATORS_2:		return "Illuminator 2";
	case V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:	return "Min Number of Capture Buffers";
	case V4L2_CID_MIN_BUFFERS_FOR_OUTPUT:	return "Min Number of Output Buffers";
	case V4L2_CID_ALPHA_COMPONENT:		return "Alpha Component";
	case V4L2_CID_COLORFX_CBCR:		return "Color Effects, CbCr";

	/* Codec controls */
	/* The MPEG controls are applicable to all codec controls
	 * and the 'MPEG' part of the define is historical */
	/* Keep the order of the 'case's the same as in videodev2.h! */
	case V4L2_CID_MPEG_CLASS:		return "Codec Controls";
	case V4L2_CID_MPEG_STREAM_TYPE:		return "Stream Type";
	case V4L2_CID_MPEG_STREAM_PID_PMT:	return "Stream PMT Program ID";
	case V4L2_CID_MPEG_STREAM_PID_AUDIO:	return "Stream Audio Program ID";
	case V4L2_CID_MPEG_STREAM_PID_VIDEO:	return "Stream Video Program ID";
	case V4L2_CID_MPEG_STREAM_PID_PCR:	return "Stream PCR Program ID";
	case V4L2_CID_MPEG_STREAM_PES_ID_AUDIO: return "Stream PES Audio ID";
	case V4L2_CID_MPEG_STREAM_PES_ID_VIDEO: return "Stream PES Video ID";
	case V4L2_CID_MPEG_STREAM_VBI_FMT:	return "Stream VBI Format";
	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ: return "Audio Sampling Frequency";
	case V4L2_CID_MPEG_AUDIO_ENCODING:	return "Audio Encoding";
	case V4L2_CID_MPEG_AUDIO_L1_BITRATE:	return "Audio Layer I Bitrate";
	case V4L2_CID_MPEG_AUDIO_L2_BITRATE:	return "Audio Layer II Bitrate";
	case V4L2_CID_MPEG_AUDIO_L3_BITRATE:	return "Audio Layer III Bitrate";
	case V4L2_CID_MPEG_AUDIO_MODE:		return "Audio Stereo Mode";
	case V4L2_CID_MPEG_AUDIO_MODE_EXTENSION: return "Audio Stereo Mode Extension";
	case V4L2_CID_MPEG_AUDIO_EMPHASIS:	return "Audio Emphasis";
	case V4L2_CID_MPEG_AUDIO_CRC:		return "Audio CRC";
	case V4L2_CID_MPEG_AUDIO_MUTE:		return "Audio Mute";
	case V4L2_CID_MPEG_AUDIO_AAC_BITRATE:	return "Audio AAC Bitrate";
	case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:	return "Audio AC-3 Bitrate";
	case V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK:	return "Audio Playback";
	case V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK: return "Audio Multilingual Playback";
	case V4L2_CID_MPEG_VIDEO_ENCODING:	return "Video Encoding";
	case V4L2_CID_MPEG_VIDEO_ASPECT:	return "Video Aspect";
	case V4L2_CID_MPEG_VIDEO_B_FRAMES:	return "Video B Frames";
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:	return "Video GOP Size";
	case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:	return "Video GOP Closure";
	case V4L2_CID_MPEG_VIDEO_PULLDOWN:	return "Video Pulldown";
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:	return "Video Bitrate Mode";
	case V4L2_CID_MPEG_VIDEO_BITRATE:	return "Video Bitrate";
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:	return "Video Peak Bitrate";
	case V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION: return "Video Temporal Decimation";
	case V4L2_CID_MPEG_VIDEO_MUTE:		return "Video Mute";
	case V4L2_CID_MPEG_VIDEO_MUTE_YUV:	return "Video Mute YUV";
	case V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE:	return "Decoder Slice Interface";
	case V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:	return "MPEG4 Loop Filter Enable";
	case V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB:	return "Number of Intra Refresh MBs";
	case V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:		return "Frame Level Rate Control Enable";
	case V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE:			return "H264 MB Level Rate Control";
	case V4L2_CID_MPEG_VIDEO_HEADER_MODE:			return "Sequence Header Mode";
	case V4L2_CID_MPEG_VIDEO_MAX_REF_PIC:			return "Max Number of Reference Pics";
	case V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP:		return "H263 I-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP:		return "H263 P-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP:		return "H263 B-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_H263_MIN_QP:			return "H263 Minimum QP Value";
	case V4L2_CID_MPEG_VIDEO_H263_MAX_QP:			return "H263 Maximum QP Value";
	case V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP:		return "H264 I-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP:		return "H264 P-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP:		return "H264 B-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_H264_MAX_QP:			return "H264 Maximum QP Value";
	case V4L2_CID_MPEG_VIDEO_H264_MIN_QP:			return "H264 Minimum QP Value";
	case V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM:		return "H264 8x8 Transform Enable";
	case V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE:			return "H264 CPB Buffer Size";
	case V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:		return "H264 Entropy Mode";
	case V4L2_CID_MPEG_VIDEO_H264_I_PERIOD:			return "H264 I-Frame Period";
	case V4L2_CID_MPEG_VIDEO_H264_LEVEL:			return "H264 Level";
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA:	return "H264 Loop Filter Alpha Offset";
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA:		return "H264 Loop Filter Beta Offset";
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:		return "H264 Loop Filter Mode";
	case V4L2_CID_MPEG_VIDEO_H264_PROFILE:			return "H264 Profile";
	case V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT:	return "Vertical Size of SAR";
	case V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH:	return "Horizontal Size of SAR";
	case V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE:		return "Aspect Ratio VUI Enable";
	case V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC:		return "VUI Aspect Ratio IDC";
	case V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING:	return "H264 Enable Frame Packing SEI";
	case V4L2_CID_MPEG_VIDEO_H264_SEI_FP_CURRENT_FRAME_0:	return "H264 Set Curr. Frame as Frame0";
	case V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE:	return "H264 FP Arrangement Type";
	case V4L2_CID_MPEG_VIDEO_H264_FMO:			return "H264 Flexible MB Ordering";
	case V4L2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE:		return "H264 Map Type for FMO";
	case V4L2_CID_MPEG_VIDEO_H264_FMO_SLICE_GROUP:		return "H264 FMO Number of Slice Groups";
	case V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_DIRECTION:	return "H264 FMO Direction of Change";
	case V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_RATE:		return "H264 FMO Size of 1st Slice Grp";
	case V4L2_CID_MPEG_VIDEO_H264_FMO_RUN_LENGTH:		return "H264 FMO No. of Consecutive MBs";
	case V4L2_CID_MPEG_VIDEO_H264_ASO:			return "H264 Arbitrary Slice Ordering";
	case V4L2_CID_MPEG_VIDEO_H264_ASO_SLICE_ORDER:		return "H264 ASO Slice Order";
	case V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING:	return "Enable H264 Hierarchical Coding";
	case V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_TYPE:	return "H264 Hierarchical Coding Type";
	case V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER:return "H264 Number of HC Layers";
	case V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER_QP:
								return "H264 Set QP Value for HC Layers";
	case V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP:		return "MPEG4 I-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP:		return "MPEG4 P-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP:		return "MPEG4 B-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP:			return "MPEG4 Minimum QP Value";
	case V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP:			return "MPEG4 Maximum QP Value";
	case V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:			return "MPEG4 Level";
	case V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE:			return "MPEG4 Profile";
	case V4L2_CID_MPEG_VIDEO_MPEG4_QPEL:			return "Quarter Pixel Search Enable";
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES:		return "Maximum Bytes in a Slice";
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB:		return "Number of MBs in a Slice";
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:		return "Slice Partitioning Method";
	case V4L2_CID_MPEG_VIDEO_VBV_SIZE:			return "VBV Buffer Size";
	case V4L2_CID_MPEG_VIDEO_DEC_PTS:			return "Video Decoder PTS";
	case V4L2_CID_MPEG_VIDEO_DEC_FRAME:			return "Video Decoder Frame Count";
	case V4L2_CID_MPEG_VIDEO_VBV_DELAY:			return "Initial Delay for VBV Control";
	case V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE:		return "Horizontal MV Search Range";
	case V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE:		return "Vertical MV Search Range";
	case V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER:		return "Repeat Sequence Header";
	case V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:		return "Force Key Frame";

	/* VPX controls */
	case V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS:		return "VPX Number of Partitions";
	case V4L2_CID_MPEG_VIDEO_VPX_IMD_DISABLE_4X4:		return "VPX Intra Mode Decision Disable";
	case V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES:		return "VPX No. of Refs for P Frame";
	case V4L2_CID_MPEG_VIDEO_VPX_FILTER_LEVEL:		return "VPX Loop Filter Level Range";
	case V4L2_CID_MPEG_VIDEO_VPX_FILTER_SHARPNESS:		return "VPX Deblocking Effect Control";
	case V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_REF_PERIOD:	return "VPX Golden Frame Refresh Period";
	case V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL:		return "VPX Golden Frame Indicator";
	case V4L2_CID_MPEG_VIDEO_VPX_MIN_QP:			return "VPX Minimum QP Value";
	case V4L2_CID_MPEG_VIDEO_VPX_MAX_QP:			return "VPX Maximum QP Value";
	case V4L2_CID_MPEG_VIDEO_VPX_I_FRAME_QP:		return "VPX I-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_VPX_P_FRAME_QP:		return "VPX P-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_VP8_PROFILE:			return "VP8 Profile";
	case V4L2_CID_MPEG_VIDEO_VP9_PROFILE:			return "VP9 Profile";

	/* HEVC controls */
	case V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP:		return "HEVC I-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP:		return "HEVC P-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP:		return "HEVC B-Frame QP Value";
	case V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP:			return "HEVC Minimum QP Value";
	case V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP:			return "HEVC Maximum QP Value";
	case V4L2_CID_MPEG_VIDEO_HEVC_PROFILE:			return "HEVC Profile";
	case V4L2_CID_MPEG_VIDEO_HEVC_LEVEL:			return "HEVC Level";
	case V4L2_CID_MPEG_VIDEO_HEVC_TIER:			return "HEVC Tier";
	case V4L2_CID_MPEG_VIDEO_HEVC_FRAME_RATE_RESOLUTION:	return "HEVC Frame Rate Resolution";
	case V4L2_CID_MPEG_VIDEO_HEVC_MAX_PARTITION_DEPTH:	return "HEVC Maximum Coding Unit Depth";
	case V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE:		return "HEVC Refresh Type";
	case V4L2_CID_MPEG_VIDEO_HEVC_CONST_INTRA_PRED:		return "HEVC Constant Intra Prediction";
	case V4L2_CID_MPEG_VIDEO_HEVC_LOSSLESS_CU:		return "HEVC Lossless Encoding";
	case V4L2_CID_MPEG_VIDEO_HEVC_WAVEFRONT:		return "HEVC Wavefront";
	case V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE:		return "HEVC Loop Filter";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_QP:			return "HEVC QP Values";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE:		return "HEVC Hierarchical Coding Type";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_LAYER:	return "HEVC Hierarchical Coding Layer";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_QP:	return "HEVC Hierarchical Layer 0 QP";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_QP:	return "HEVC Hierarchical Layer 1 QP";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_QP:	return "HEVC Hierarchical Layer 2 QP";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_QP:	return "HEVC Hierarchical Layer 3 QP";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_QP:	return "HEVC Hierarchical Layer 4 QP";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_QP:	return "HEVC Hierarchical Layer 5 QP";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_QP:	return "HEVC Hierarchical Layer 6 QP";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_BR:	return "HEVC Hierarchical Lay 0 BitRate";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_BR:	return "HEVC Hierarchical Lay 1 BitRate";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_BR:	return "HEVC Hierarchical Lay 2 BitRate";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_BR:	return "HEVC Hierarchical Lay 3 BitRate";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_BR:	return "HEVC Hierarchical Lay 4 BitRate";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_BR:	return "HEVC Hierarchical Lay 5 BitRate";
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_BR:	return "HEVC Hierarchical Lay 6 BitRate";
	case V4L2_CID_MPEG_VIDEO_HEVC_GENERAL_PB:		return "HEVC General PB";
	case V4L2_CID_MPEG_VIDEO_HEVC_TEMPORAL_ID:		return "HEVC Temporal ID";
	case V4L2_CID_MPEG_VIDEO_HEVC_STRONG_SMOOTHING:		return "HEVC Strong Intra Smoothing";
	case V4L2_CID_MPEG_VIDEO_HEVC_INTRA_PU_SPLIT:		return "HEVC Intra PU Split";
	case V4L2_CID_MPEG_VIDEO_HEVC_TMV_PREDICTION:		return "HEVC TMV Prediction";
	case V4L2_CID_MPEG_VIDEO_HEVC_MAX_NUM_MERGE_MV_MINUS1:	return "HEVC Max Num of Candidate MVs";
	case V4L2_CID_MPEG_VIDEO_HEVC_WITHOUT_STARTCODE:	return "HEVC ENC Without Startcode";
	case V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_PERIOD:		return "HEVC Num of I-Frame b/w 2 IDR";
	case V4L2_CID_MPEG_VIDEO_HEVC_LF_BETA_OFFSET_DIV2:	return "HEVC Loop Filter Beta Offset";
	case V4L2_CID_MPEG_VIDEO_HEVC_LF_TC_OFFSET_DIV2:	return "HEVC Loop Filter TC Offset";
	case V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD:	return "HEVC Size of Length Field";
	case V4L2_CID_MPEG_VIDEO_REF_NUMBER_FOR_PFRAMES:	return "Reference Frames for a P-Frame";
	case V4L2_CID_MPEG_VIDEO_PREPEND_SPSPPS_TO_IDR:		return "Prepend SPS and PPS to IDR";

	/* CAMERA controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	case V4L2_CID_CAMERA_CLASS:		return "Camera Controls";
	case V4L2_CID_EXPOSURE_AUTO:		return "Auto Exposure";
	case V4L2_CID_EXPOSURE_ABSOLUTE:	return "Exposure Time, Absolute";
	case V4L2_CID_EXPOSURE_AUTO_PRIORITY:	return "Exposure, Dynamic Framerate";
	case V4L2_CID_PAN_RELATIVE:		return "Pan, Relative";
	case V4L2_CID_TILT_RELATIVE:		return "Tilt, Relative";
	case V4L2_CID_PAN_RESET:		return "Pan, Reset";
	case V4L2_CID_TILT_RESET:		return "Tilt, Reset";
	case V4L2_CID_PAN_ABSOLUTE:		return "Pan, Absolute";
	case V4L2_CID_TILT_ABSOLUTE:		return "Tilt, Absolute";
	case V4L2_CID_FOCUS_ABSOLUTE:		return "Focus, Absolute";
	case V4L2_CID_FOCUS_RELATIVE:		return "Focus, Relative";
	case V4L2_CID_FOCUS_AUTO:		return "Focus, Automatic Continuous";
	case V4L2_CID_ZOOM_ABSOLUTE:		return "Zoom, Absolute";
	case V4L2_CID_ZOOM_RELATIVE:		return "Zoom, Relative";
	case V4L2_CID_ZOOM_CONTINUOUS:		return "Zoom, Continuous";
	case V4L2_CID_PRIVACY:			return "Privacy";
	case V4L2_CID_IRIS_ABSOLUTE:		return "Iris, Absolute";
	case V4L2_CID_IRIS_RELATIVE:		return "Iris, Relative";
	case V4L2_CID_AUTO_EXPOSURE_BIAS:	return "Auto Exposure, Bias";
	case V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE: return "White Balance, Auto & Preset";
	case V4L2_CID_WIDE_DYNAMIC_RANGE:	return "Wide Dynamic Range";
	case V4L2_CID_IMAGE_STABILIZATION:	return "Image Stabilization";
	case V4L2_CID_ISO_SENSITIVITY:		return "ISO Sensitivity";
	case V4L2_CID_ISO_SENSITIVITY_AUTO:	return "ISO Sensitivity, Auto";
	case V4L2_CID_EXPOSURE_METERING:	return "Exposure, Metering Mode";
	case V4L2_CID_SCENE_MODE:		return "Scene Mode";
	case V4L2_CID_3A_LOCK:			return "3A Lock";
	case V4L2_CID_AUTO_FOCUS_START:		return "Auto Focus, Start";
	case V4L2_CID_AUTO_FOCUS_STOP:		return "Auto Focus, Stop";
	case V4L2_CID_AUTO_FOCUS_STATUS:	return "Auto Focus, Status";
	case V4L2_CID_AUTO_FOCUS_RANGE:		return "Auto Focus, Range";
	case V4L2_CID_PAN_SPEED:		return "Pan, Speed";
	case V4L2_CID_TILT_SPEED:		return "Tilt, Speed";

	/* FM Radio Modulator controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	case V4L2_CID_FM_TX_CLASS:		return "FM Radio Modulator Controls";
	case V4L2_CID_RDS_TX_DEVIATION:		return "RDS Signal Deviation";
	case V4L2_CID_RDS_TX_PI:		return "RDS Program ID";
	case V4L2_CID_RDS_TX_PTY:		return "RDS Program Type";
	case V4L2_CID_RDS_TX_PS_NAME:		return "RDS PS Name";
	case V4L2_CID_RDS_TX_RADIO_TEXT:	return "RDS Radio Text";
	case V4L2_CID_RDS_TX_MONO_STEREO:	return "RDS Stereo";
	case V4L2_CID_RDS_TX_ARTIFICIAL_HEAD:	return "RDS Artificial Head";
	case V4L2_CID_RDS_TX_COMPRESSED:	return "RDS Compressed";
	case V4L2_CID_RDS_TX_DYNAMIC_PTY:	return "RDS Dynamic PTY";
	case V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT: return "RDS Traffic Announcement";
	case V4L2_CID_RDS_TX_TRAFFIC_PROGRAM:	return "RDS Traffic Program";
	case V4L2_CID_RDS_TX_MUSIC_SPEECH:	return "RDS Music";
	case V4L2_CID_RDS_TX_ALT_FREQS_ENABLE:	return "RDS Enable Alt Frequencies";
	case V4L2_CID_RDS_TX_ALT_FREQS:		return "RDS Alternate Frequencies";
	case V4L2_CID_AUDIO_LIMITER_ENABLED:	return "Audio Limiter Feature Enabled";
	case V4L2_CID_AUDIO_LIMITER_RELEASE_TIME: return "Audio Limiter Release Time";
	case V4L2_CID_AUDIO_LIMITER_DEVIATION:	return "Audio Limiter Deviation";
	case V4L2_CID_AUDIO_COMPRESSION_ENABLED: return "Audio Compression Enabled";
	case V4L2_CID_AUDIO_COMPRESSION_GAIN:	return "Audio Compression Gain";
	case V4L2_CID_AUDIO_COMPRESSION_THRESHOLD: return "Audio Compression Threshold";
	case V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME: return "Audio Compression Attack Time";
	case V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME: return "Audio Compression Release Time";
	case V4L2_CID_PILOT_TONE_ENABLED:	return "Pilot Tone Feature Enabled";
	case V4L2_CID_PILOT_TONE_DEVIATION:	return "Pilot Tone Deviation";
	case V4L2_CID_PILOT_TONE_FREQUENCY:	return "Pilot Tone Frequency";
	case V4L2_CID_TUNE_PREEMPHASIS:		return "Pre-Emphasis";
	case V4L2_CID_TUNE_POWER_LEVEL:		return "Tune Power Level";
	case V4L2_CID_TUNE_ANTENNA_CAPACITOR:	return "Tune Antenna Capacitor";

	/* Flash controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	case V4L2_CID_FLASH_CLASS:		return "Flash Controls";
	case V4L2_CID_FLASH_LED_MODE:		return "LED Mode";
	case V4L2_CID_FLASH_STROBE_SOURCE:	return "Strobe Source";
	case V4L2_CID_FLASH_STROBE:		return "Strobe";
	case V4L2_CID_FLASH_STROBE_STOP:	return "Stop Strobe";
	case V4L2_CID_FLASH_STROBE_STATUS:	return "Strobe Status";
	case V4L2_CID_FLASH_TIMEOUT:		return "Strobe Timeout";
	case V4L2_CID_FLASH_INTENSITY:		return "Intensity, Flash Mode";
	case V4L2_CID_FLASH_TORCH_INTENSITY:	return "Intensity, Torch Mode";
	case V4L2_CID_FLASH_INDICATOR_INTENSITY: return "Intensity, Indicator";
	case V4L2_CID_FLASH_FAULT:		return "Faults";
	case V4L2_CID_FLASH_CHARGE:		return "Charge";
	case V4L2_CID_FLASH_READY:		return "Ready to Strobe";

	/* JPEG encoder controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	case V4L2_CID_JPEG_CLASS:		return "JPEG Compression Controls";
	case V4L2_CID_JPEG_CHROMA_SUBSAMPLING:	return "Chroma Subsampling";
	case V4L2_CID_JPEG_RESTART_INTERVAL:	return "Restart Interval";
	case V4L2_CID_JPEG_COMPRESSION_QUALITY:	return "Compression Quality";
	case V4L2_CID_JPEG_ACTIVE_MARKER:	return "Active Markers";

	/* Image source controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	case V4L2_CID_IMAGE_SOURCE_CLASS:	return "Image Source Controls";
	case V4L2_CID_VBLANK:			return "Vertical Blanking";
	case V4L2_CID_HBLANK:			return "Horizontal Blanking";
	case V4L2_CID_ANALOGUE_GAIN:		return "Analogue Gain";
	case V4L2_CID_TEST_PATTERN_RED:		return "Red Pixel Value";
	case V4L2_CID_TEST_PATTERN_GREENR:	return "Green (Red) Pixel Value";
	case V4L2_CID_TEST_PATTERN_BLUE:	return "Blue Pixel Value";
	case V4L2_CID_TEST_PATTERN_GREENB:	return "Green (Blue) Pixel Value";

	/* Image processing controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	case V4L2_CID_IMAGE_PROC_CLASS:		return "Image Processing Controls";
	case V4L2_CID_LINK_FREQ:		return "Link Frequency";
	case V4L2_CID_PIXEL_RATE:		return "Pixel Rate";
	case V4L2_CID_TEST_PATTERN:		return "Test Pattern";
	case V4L2_CID_DEINTERLACING_MODE:	return "Deinterlacing Mode";
	case V4L2_CID_DIGITAL_GAIN:		return "Digital Gain";

	/* DV controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	case V4L2_CID_DV_CLASS:			return "Digital Video Controls";
	case V4L2_CID_DV_TX_HOTPLUG:		return "Hotplug Present";
	case V4L2_CID_DV_TX_RXSENSE:		return "RxSense Present";
	case V4L2_CID_DV_TX_EDID_PRESENT:	return "EDID Present";
	case V4L2_CID_DV_TX_MODE:		return "Transmit Mode";
	case V4L2_CID_DV_TX_RGB_RANGE:		return "Tx RGB Quantization Range";
	case V4L2_CID_DV_TX_IT_CONTENT_TYPE:	return "Tx IT Content Type";
	case V4L2_CID_DV_RX_POWER_PRESENT:	return "Power Present";
	case V4L2_CID_DV_RX_RGB_RANGE:		return "Rx RGB Quantization Range";
	case V4L2_CID_DV_RX_IT_CONTENT_TYPE:	return "Rx IT Content Type";

	case V4L2_CID_FM_RX_CLASS:		return "FM Radio Receiver Controls";
	case V4L2_CID_TUNE_DEEMPHASIS:		return "De-Emphasis";
	case V4L2_CID_RDS_RECEPTION:		return "RDS Reception";
	case V4L2_CID_RF_TUNER_CLASS:		return "RF Tuner Controls";
	case V4L2_CID_RF_TUNER_RF_GAIN:		return "RF Gain";
	case V4L2_CID_RF_TUNER_LNA_GAIN_AUTO:	return "LNA Gain, Auto";
	case V4L2_CID_RF_TUNER_LNA_GAIN:	return "LNA Gain";
	case V4L2_CID_RF_TUNER_MIXER_GAIN_AUTO:	return "Mixer Gain, Auto";
	case V4L2_CID_RF_TUNER_MIXER_GAIN:	return "Mixer Gain";
	case V4L2_CID_RF_TUNER_IF_GAIN_AUTO:	return "IF Gain, Auto";
	case V4L2_CID_RF_TUNER_IF_GAIN:		return "IF Gain";
	case V4L2_CID_RF_TUNER_BANDWIDTH_AUTO:	return "Bandwidth, Auto";
	case V4L2_CID_RF_TUNER_BANDWIDTH:	return "Bandwidth";
	case V4L2_CID_RF_TUNER_PLL_LOCK:	return "PLL Lock";
	case V4L2_CID_RDS_RX_PTY:		return "RDS Program Type";
	case V4L2_CID_RDS_RX_PS_NAME:		return "RDS PS Name";
	case V4L2_CID_RDS_RX_RADIO_TEXT:	return "RDS Radio Text";
	case V4L2_CID_RDS_RX_TRAFFIC_ANNOUNCEMENT: return "RDS Traffic Announcement";
	case V4L2_CID_RDS_RX_TRAFFIC_PROGRAM:	return "RDS Traffic Program";
	case V4L2_CID_RDS_RX_MUSIC_SPEECH:	return "RDS Music";

	/* Detection controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	case V4L2_CID_DETECT_CLASS:		return "Detection Controls";
	case V4L2_CID_DETECT_MD_MODE:		return "Motion Detection Mode";
	case V4L2_CID_DETECT_MD_GLOBAL_THRESHOLD: return "MD Global Threshold";
	case V4L2_CID_DETECT_MD_THRESHOLD_GRID:	return "MD Threshold Grid";
	case V4L2_CID_DETECT_MD_REGION_GRID:	return "MD Region Grid";
	default:
		return NULL;
	}
}